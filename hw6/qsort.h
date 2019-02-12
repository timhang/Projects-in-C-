#include<vector>
#include<string>
struct AlphaStrComp {
    bool operator()(const std::string& lhs, const std::string& rhs);
     // Uses string's built in operator< 
      // to do lexicographic (alphabetical) comparison
  };

struct NumStrComp {
    bool operator()(const std::string& lhs, const std::string& rhs);
  };

template <class T, class Comparator>
void quickSort_helper(std::vector<T>& vec, int low, int high, Comparator comp){
	if (low < high)
    {
    T vechigh = vec[high];
	T veclow = vec[low];
	T max;
	int mark;
	T pivot;
	int pivot_index;
	T medium = vec[(high+low)/2];
	if(comp(vechigh,veclow)==false){
		max = vechigh;
		mark = 1;
	}
	else{
		max = veclow;
		mark = 2;
	}
	if(comp(max,medium)){
		max = medium;
		mark = 3;
	}
	switch(mark){
		case 1:
			if(comp(medium,veclow)==false){
				pivot = medium;
				pivot_index = (high+low)/2;
			} 
			else{
				pivot = veclow;
				pivot_index = low;
			}
			break;
		case 2:
			if(comp(vechigh,medium)==false){
				pivot = vechigh;
				pivot_index = high;
			}
			else{
				pivot = medium;
				pivot_index = (high+low)/2;
			}
			break;
		case 3:
			if(comp(vechigh,veclow)==false){
				pivot = vechigh;
				pivot_index = high;
			}
			else{
				pivot = veclow;
				pivot_index = low;
			}
			break;

	}
	T temp = vec[pivot_index];
	vec[pivot_index] = vec[low];
	vec[low] = temp;
	int i = low+1;
	int j = high;
	while(i<=j){
		while(i<=j && comp(vec[i],pivot))
			i++;

		while(i<=j && (comp(vec[j],pivot)==false))
			j--;

		if(i<j){
			temp = vec[i];
			vec[i] = vec[j];
			vec[j] = temp;
		}

	}
	
	temp = vec[i-1];
	vec[i-1] = vec[low];
	vec[low] = temp;
        quickSort_helper(vec, low, j,comp);
        quickSort_helper(vec, i, high,comp);
    }
}

template <class T, class Comparator>
void QuickSort(std::vector<T>& vec, Comparator comp)
{
    quickSort_helper(vec,0,int(vec.size()-1),comp);
    
}