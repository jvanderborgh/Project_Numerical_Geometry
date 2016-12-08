#pragma once

/*
 * This library is for performed delaunay triangulation using an incremental algorithm
 */

#include <algorithm> // useful for std::min N'est pas reconnu! :-(
 
#include <memory>
// #include <vector>;
#include <iostream>

class Point;
class Segment;
class Triangle;

// Typedef is used to define new types of variables
// Here we create the type "Tptr" and "Edge"
  	/* More explanation about std::call below */

// Pointeurs qui partagent le même triangle :-)
typedef std::shared_ptr<Triangle>  Tptr; // Pointeur partagé de triangle 
typedef std::tuple<int,int,Tptr>   Edge; 

class Point
{
  public:

    double x, y, z;
 	  /* 
      Selon qu'on appelle Point avec 2 ou 3 arguments, la définition
      de l'objet est différent :-)
    */
    Point(double x, double y)           : x(x), y(y), z(0) 
    {/* Il n'y as pas de méthodes définies sur cet objet :-) */}
    Point(double x, double y, double z) : x(x), y(y), z(z) 
    {/* Il n'y as pas de méthodes définies sur cet objet :-) */}
};

/* Redefinition of the operators for Points objects*/
Point operator+(const Point &a, const Point &b)
{
  return Point(a.x+b.x, a.y+b.y, a.z+b.z);
}

Point operator-(const Point &a, const Point &b)
{
  return Point(a.x-b.x, a.y-b.y, a.z-b.z);
}

Point operator*(const double &s, const Point &b)
{
  return Point(s*b.x, s*b.y, s*b.z);
}

/* Produit d'amplifcation (par constante s) */
Point operator*(const Point &b, const double &s)
{
  return s*b;
}
/* Produit scalaire */
double dot(const Point a, const Point b)
{
  return (a.x*b.x + a.y*b.y + a.z*b.z);
}
/* Produit vectoriel */
Point cross(const Point a, const Point b)
{
  return Point( a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x );
}

class Triangle
{
  public:
    std::array<int, 3> v;     // Holds the verticies
    std::array<Tptr,3> n;     // Holds the neighbours
                              //3 pointeurs qui partagent le même référence d'un triangle

    Triangle(int a, int b, int c) : v {{a, b, c}}
    {
      n.fill(nullptr);
    }

    void SetEdge(const Edge edge, const Tptr T)
    {
      // Set the edge neighbour that matches "edge" to T

      for (int i: {0, 1, 2})
      {
        if (std::get<0>(edge) == v[i] && std::get<1>(edge) == v[(i+1)%3])
        {
          n[(i+2)%3] = T;
          return;
        }
      }
    }
};

/*
  Function that make usable the operator << to display all the vertices
  the triangle T.
  The code displays a triangle using the cout object
  Example of calling: cout << T (where T is a variable of type Tptr and
  containing shared_ptr<Triangle> where Triangle is an object)
  Thanks to that, 'cout' will accept the use of a Tptr variable after
  insertion of <<.
*/
std::ostream& operator<<(std::ostream& os, const Tptr& T)
{
    os << "(" << T->v[0] << ',' << T->v[1] << ',' << T->v[2] << "),";
    return os;
}

/*
	Class Delaunay Triangulation
	BIG FAT OBJECT :-)
*/
class DelaunayTriangulation
{
  /* FIRST WE START WITH THE PUBLIC METHODS */
  public:

    std::vector<Point> points;    // Create a vector of points (Point)
    std::vector<Tptr>  triangles; // Create a vector of triangles (Tptr)

    DelaunayTriangulation(int width, int height)
    {
      /*
          The following points will be the frame of our triangulation
      */
      points.push_back( Point(0,     0) ); // Centering the first point on (0,0)
      points.push_back( Point(width, 0) ); // Add a point to the right
      points.push_back( Point(width, height) ); // Add a point above to the right
      points.push_back( Point(0,     height) ); // Add a point above

      /*
        Form the frame and create two basic triangles
        
        Code comments:

        -shared_ptr<T> make_shared( Args... args );
        Construit un objet de type de T et l'enveloppe dans un std::shared_ptr 
        utilisant args que la liste des paramètres pour le constructeur de T .

        -auto variable initializer
        Spécifie que le type de la variable qui est déclarée sera automatiquement déduit de son initialisation. Pour les fonctions, indique que le type de retour est un type de retour de fuite .

      */

      auto T1 = std::make_shared<Triangle>(0, 3, 1);
      auto T2 = std::make_shared<Triangle>(2, 1, 3);

      /*
          Putting each other the triangles as neighbours 
      */
      T1->n[0] = T2;
      T2->n[0] = T1;

      /* Add the two new created triangles */
      triangles.push_back(T1);
      triangles.push_back(T2);
    }

    void print()
    {
      using namespace std; // http://cpp.developpez.com/faq/cpp/?page=Les-namespaces#Qu-est-ce-qu-un-namespace

      cout << "Points" << endl;
      for (auto p : points) /* For all points, print the points */
        cout << p << endl;

      cout << endl << "Triangles" << endl;
      for (auto t : triangles) /* For all triangles, print the triangles */
        cout << t << endl;
        /* os << "(" << T->v[0] << ',' << T->v[1] << ',' << T->v[2] << "),"; */
    }

    void AddPoint(Point p)
    {
      points.push_back(p);
      int pi = points.size() - 1;

      std::vector<Tptr> bad_triangles;

      /* For now I am just doing a naive search 
         Car il fait une boucle for sur tous les triangles jusqu'à trouver le bon!
         C'est pas très efficace...
         I hope to replace this one day with something different
         Nous on va devoir réaliser via l'algorithme du cours!!!
      */
      for (auto T : triangles)
      {
        if (CircumcircleContains(T, p))
        bad_triangles.push_back(T); /* On répertorie le triangle contenant p*/
      }

      // Find the boundary/edges of the bad triangles. See function below :-)
      std::vector<Edge> boundary = GetBoundary(bad_triangles);

      /* 
        **** Remove all the bad triangles from the list of triangles ****
        Note that all the bad triangles are the ones concerned by the point p
        This is the one containing the point p BUT ALSO the ones who are the
        neighbours of this last triangle...

        Code comments: 
        http://fr.cppreference.com/w/cpp/container/vector/erase used in parallel with std::remove
        Very simple example given here: http://fr.cppreference.com/w/cpp/algorithm/remove

        For remind, 'triangles' is a public variables in class DelaunayTriangulation
      */

      for (auto T : bad_triangles)
        triangles.erase(std::remove(triangles.begin(),triangles.end(), T), triangles.end());

      /* Retriangle the hole just created */
      std::vector<Tptr> new_triangles;
      for (auto edge : boundary)
      {
        int a = std::get<0>(edge);
        int b = std::get<1>(edge);

        auto T = std::make_shared<Triangle>(pi, a, b);

        T->n[0] = std::get<2>(edge);  // To neighbour
        
        if (std::get<2>(edge))
          T->n[0]->SetEdge(Edge(b, a, nullptr), T);  // From neighbour

        new_triangles.push_back(T);
      }

      // Link the new triangles to each other
      int N = new_triangles.size();
      for (int i = 0; i < N; i++)
      {
        new_triangles[i]->n[2] = new_triangles[((i-1) % N + N) % N];
        new_triangles[i]->n[1] = new_triangles[(i+1) % N];
      }

      triangles.reserve(triangles.size() + distance(new_triangles.begin(), new_triangles.end()));
      triangles.insert(triangles.end(), new_triangles.begin(), new_triangles.end());
    }

  /* HERE WE CONTINUE WITH THE PRIVATE METHODS */
  private:

    // Check whether the circumcirlce of T contains p
    bool CircumcircleContains(Tptr T, Point p)
    {
      Point a = points[T->v[0]] - points[T->v[2]];
      Point b = points[T->v[1]] - points[T->v[2]];

      // Ref: https://en.wikipedia.org/wiki/Circumscribed_circle#Circumcircle_equations
      Point z  = cross(a,b);
      Point p0 = cross(dot(a,a)*b-dot(b,b)*a, z)*(0.5/dot(z,z)) + points[T->v[2]];

      double r2 = 0.25*dot(a, a)*dot(b,b)*dot(a-b, a-b)/dot(z, z);

      return (dot(p-p0, p-p0) <= r2);
    }

    std::vector<Edge> GetBoundary(std::vector<Tptr> bad_triangles)
    {

      // Start with a triangle at random from the vector bad triangles
      Tptr T = bad_triangles[0];
      int edge = 0;

      // Create empty boundary list
      std::vector<Edge> boundary;

      while (true)
      {   
        if (boundary.size() > 1)
          if (boundary.front() == boundary.back())
            break;

        // Check if this edge is shared with a triangle in bad_triangles.
        if (std::find(bad_triangles.begin(), bad_triangles.end(), T->n[edge]) != bad_triangles.end())
        {
          // If so set current triangle
          Tptr last = T;
          T = T->n[edge];

          int pos = find(T->n.begin(), T->n.end(), last) - T->n.begin();
          edge = (pos + 1) % 3;
        }

        else // Found an edge that is on the boundary 
        {
          // Add to list

          Edge new_edge(T->v[(edge+1)%3], T->v[(edge+2)%3], T->n[edge]);
          boundary.push_back( new_edge );
          edge = (edge + 1) % 3;
        }
      }

      boundary.pop_back();
      return boundary;
    }
};
