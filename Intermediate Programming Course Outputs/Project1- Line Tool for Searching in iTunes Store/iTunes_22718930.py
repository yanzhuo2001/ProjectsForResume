#########################################
##### Name: Yanzhuo Cao             #####
##### Uniqname:  yanzhuo            #####
#########################################

import requests
import webbrowser


class Media:
    def __init__(self, title="No Title", author="No Author", release_year="No Release Year", url=None, json=None):
        if json:
            if json.get("wrapperType")!= "track":
                self.title = json.get("collectionName", title)
            else:
                self.title = json.get("trackName", title)
            self.author = json.get("artistName", author)
            self.release_year = str(json.get("releaseDate", release_year).split("-")[0])
            self.url = json.get("collectionViewUrl", url)
        else:
            self.title = title
            self.author = author
            self.release_year = release_year
            self.url = url

    def info(self):
        return f"{self.title} by {self.author} ({self.release_year})"

    def length(self):
        return 0


class Song(Media):
    def __init__(self, title="No Title", author="No Author", release_year="No Release Year", url=None, album="No Album", genre="No Genre", track_length=0, json=None):
        super().__init__(title, author, release_year, url, json)
        if json:
            self.album = json.get("collectionName", album)
            self.genre = json.get("primaryGenreName", genre)
            self.track_length = json.get("trackTimeMillis", track_length)
        else:
            self.album = album
            self.genre = genre
            self.track_length = track_length

    def info(self):
        return f"{self.title} by {self.author} ({self.release_year}) [{self.genre}]"

    def length(self):
        return int(self.track_length / 1000)  # Convert milliseconds to seconds


class Movie(Media):
    def __init__(self, title="No Title", author="No Author", release_year="No Release Year", url=None, rating="No Rating", movie_length=0, json=None):
        super().__init__(title, author, release_year, url, json)
        if json:
            self.rating = json.get("contentAdvisoryRating", rating)
            self.movie_length = json.get("trackTimeMillis", movie_length)
        else:
            self.rating = rating
            self.movie_length = movie_length

    def info(self):
        return f"{self.title} by {self.author} ({self.release_year}) [{self.rating}]"

    def length(self):
        return int(self.movie_length / 60000)  # Convert milliseconds to minutes


def fetch_data_from_itunes(query, limit=50):
    url = f"https://itunes.apple.com/search?term={query}&limit={limit}"
    response = requests.get(url)
    data = response.json()
    results = data["results"]

    songs, movies, other_media = [], [], []

    for result in results:
        kind = result.get("wrapperType")
        if kind == "track" and result.get("kind") == "feature-movie":
            movies.append(Movie(json=result))
        elif kind == "track" and result.get("kind") == "song":
            songs.append(Song(json=result))
        else:
            other_media.append(Media(json=result))

    return songs, movies, other_media

def interactive_search():
    prompt = 'Enter a search term, or "exit" to quit: '
    all_media = []  # 初始化为一个空列表
    previous_search_performed = False

    while True:
        user_input = input(prompt)

        if user_input.lower() == 'exit':
            print("Bye!")
            break

        if user_input.isdigit():
            choice = int(user_input) - 1
            if previous_search_performed and 0 <= choice < len(all_media):
                if all_media[choice].url:  # Check if the URL is not None
                    webbrowser.open(all_media[choice].url)
                    print(f"Launching\n{all_media[choice].url}\nin web browser...")
                else:
                    print("Cannot open the URL for this result. Please enter a number again for more info, or another search term, or exit:")
            else:
                songs, movies, other_media = fetch_data_from_itunes(user_input)
                all_media = songs + movies + other_media
                display_results(songs, movies, other_media)
                previous_search_performed = True
        else:
            songs, movies, other_media = fetch_data_from_itunes(user_input)
            all_media = songs + movies + other_media
            display_results(songs, movies, other_media)
            previous_search_performed = True

        prompt = 'Enter a number for more info, or another search term, or exit: '

def display_results(songs, movies, other_media):
    if not songs and not movies and not other_media:
        print("No results found. Try another search term.")
        return

    if songs:
        print("SONGS")
        for index, song in enumerate(songs, 1):
            print(f"{index} {song.info()}")
        print()

    if movies:
        print("MOVIES")
        for index, movie in enumerate(movies, len(songs) + 1):
            print(f"{index} {movie.info()}")
        print()

    if other_media:
        print("OTHER MEDIA")
        for index, media in enumerate(other_media, len(songs) + len(movies) + 1):
            print(f"{index} {media.info()}")
        print()

if __name__ == "__main__":
    interactive_search()

