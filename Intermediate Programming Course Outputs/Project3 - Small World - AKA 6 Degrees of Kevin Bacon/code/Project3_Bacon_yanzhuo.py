import collections

class MovieGraph:
    def __init__(self):
        '''
        Initialize the MovieGraph class.

        Parameters
        ----------
        None

        Attributes
        ----------
        actors: defaultdict(set)
            A dictionary with actors as keys and the set of movies they've acted in as values.
        movies: defaultdict(set)
            A dictionary with movies as keys and the set of actors in that movie as values.
        '''
        self.actors = collections.defaultdict(set)
        self.movies = collections.defaultdict(set)

    def add_movie_cast(self, movie, cast):
        '''
        Add a movie and its cast to the graph.

        Parameters
        ----------
        movie: str
            The name of the movie.
        cast: set
            A set of actors names in the movie.

        Returns
        -------
        None
        '''
        self.movies[movie].update(cast)
        for actor in cast:
            self.actors[actor].add(movie)

    def load_data(self, filename):
        '''
        Load movie and cast data from a file.

        Parameters
        ----------
        filename: str
            The name of the file containing the movie cast data.

        Returns
        -------
        None
        '''
        with open(filename, 'r', encoding='Windows-1252') as f:
            current_movie = ""
            current_cast = set()
            for line in f:
                parts = line.split('/')
                current_movie = parts[0].strip()
                current_cast = set(part.strip() for part in parts[1:])
                self.add_movie_cast(current_movie, current_cast)

    def find_shortest_path(self, start_actor, end_actor):
        '''
        Find the shortest path between two actors through the movies they've acted in.

        Parameters
        ----------
        start_actor: str
            The name of the starting actor.
        end_actor: str
            The name of the ending actor.

        Returns
        -------
        tuple
            A tuple with two elements: a list representing the path of actors and movies and an integer for the path length.
        '''
        if start_actor == end_actor:
            return [start_actor], 0

        visited = set()
        queue = collections.deque([(start_actor, [], 0)])

        while queue:
            current_actor, path, distance = queue.popleft()
            if current_actor == end_actor:
                return path + [end_actor], distance // 2

            if current_actor not in visited:
                visited.add(current_actor)

                for movie in self.actors[current_actor]:
                    if movie not in path:
                        for actor in self.movies[movie]:
                            if actor not in visited:
                                queue.append((actor, path + [current_actor, movie], distance + 1))

        return [], -1

    def compute_average_distance(self, start_actor):
        '''
        Compute the average distance from the start_actor to all other actors in the graph.

        Parameters
        ----------
        start_actor: str
            The name of the actor to compute distances from.

        Returns
        -------
        float
            The average distance to all other actors from the start_actor.
        '''
        visited = set()
        queue = collections.deque([(start_actor, 0)])
        total_distance = 0
        num_actors = 0

        while queue:
            current_actor, distance = queue.popleft()

            if current_actor != start_actor:
                total_distance += distance // 2
                num_actors += 1

            if current_actor not in visited:
                visited.add(current_actor)

                for movie in self.actors[current_actor]:
                    for actor in self.movies[movie]:
                        if actor not in visited:
                            queue.append((actor, distance + 1))

        if num_actors == 0:
            return 0

        return total_distance / num_actors

def main():
    graph = MovieGraph()
    graph.load_data("BaconData\BaconCastFull.txt")

    start_actor = "Bacon, Kevin"
    end_actor = "Puzic, Milan"

    path, distance = graph.find_shortest_path(start_actor, end_actor)
    distance = distance + 1
    if path:
        print("Shortest path from {} to {} is: {}".format(start_actor, end_actor, " -> ".join(path)))
        print("Distance: {}".format(distance))
    else:
        print("No path found")

    average_distance = graph.compute_average_distance(start_actor)
    average_distance = average_distance + 1
    print("Average distance of all actors to {} is: {}".format(start_actor, average_distance))

if __name__ == "__main__":
    main()
