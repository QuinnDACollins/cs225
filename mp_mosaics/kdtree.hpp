/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <list>
using namespace std;

template <int Dim>
double KDTree<Dim>::getDist(const Point<Dim>& first, const Point<Dim>& second) const {
  double sum = 0;

  for (unsigned i = 0; i < Dim; i++){
    sum += pow(first[i] - second[i], 2);
  }

  return sqrt(sum);
}
template <int Dim>
int KDTree<Dim>::partition (vector<Point<Dim>>& arr, int dim, int low, int high) 
{ 
    int pivot = arr[high][dim];    
    int i = (low - 1);
  
    for (int j = low; j <= high- 1; j++) 
    { 
  
        if (arr[j][dim] <= pivot) 
        { 
            i++;    
            std::swap(arr[i], arr[j]); 
        } 
    } 
    std::swap(arr[i + 1], arr[high]); 
    return (i + 1); 
} 
  
/* The main function that implements QuickSort 
 arr[] --> Array to be sorted, 
  low  --> Starting index, 
  high  --> Ending index */
template <int Dim>  
void KDTree<Dim>::quickSort(vector<Point<Dim>>& arr, int dim, int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
           at right place */
        int pi = partition(arr, dim, low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quickSort(arr, dim, low, pi - 1); 
        quickSort(arr, dim, pi + 1, high); 
    } 
} 

template <int Dim>
  typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::decompose(int n, int d, const vector<Point<Dim>>& p){
    
 
  if(p.size() == 1){
    KDTreeNode* temp = new KDTreeNode(p[0]);
    return temp;
  }

  int dimension = 0;
  if(d % 2 != 0){
    dimension = 1;
  }

  std::cout<<n<<std::endl;
  

  const Point<Dim> place = p[n];
  KDTreeNode* c = new KDTreeNode(place);

  auto one = p.begin() + n-1;
  auto two = p.begin() + n+1;

  std::vector<Point<Dim>> L(p.begin(), one);
  std::vector<Point<Dim>> R(two, p.end());
  
  c->left = decompose(floor((L.size() - 1) / 2), d + 1, L);
  c->right = decompose(floor((R.size() - 1) / 2), d + 1, R);
  return c;
}


template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim] != second[curDim]){
      return (first[curDim] < second[curDim]);
    } else {
      return first < second;
    }
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */

    double p_dist = getDist(potential, target);
    double c_dist = getDist(target, currentBest);
    if(p_dist != c_dist){
      return p_dist < c_dist;
    }
    return potential < currentBest;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<Dim>> build(newPoints);
    size = newPoints.size();
    quickSort(build, 0, 0, build.size() - 1);
    if(build.size() > 0){
      root = decompose(floor((build.size() - 1) /2), 0, build);
    }
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */

}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return Point<Dim>();
}

