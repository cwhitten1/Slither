#ifndef ARRAYLIST_H
#define ARRAYLIST_H

template <class T>
class ArrayList
{
    public:
        virtual ~ArrayList(){delete[] values;}
        ArrayList(){values = new T[40];nextIndex = 0;size=0; maxSize =40;}
        int Getsize() { return size; }
        int GetnextIndex() { return nextIndex; }
        void add(T val)
            {if(nextIndex == maxSize)
                    expandArray();
             values[nextIndex] = val; //Add to end of list
             nextIndex++;
             size++;}
        T get(int index){return values[index];}
        void set(int index, T val){values[index] = val;}
        int find(T val)
            {
                for(int i = 0; i < size; i++)
                {
                    T curr = get(i);
                    if(curr == val)
                        return i;
                }
                return -1;//If no match is found
            } //Returns the index of first match
        void remove(int index)
            {
                for(int i = index+1; i <size; i++)
                    values[i-1] = values[i];
                values[size-1] = T();//Clear the value in memory
                size--;
                nextIndex--;
            }
        void addAll(ArrayList<T>* inlist)
        {
            for(int i = 0; i < inlist->Getsize(); i++)
            {
                add(inlist->get(i));
            }
        }
        void addAll(ArrayList<T> inlist)
        {
            for(int i = 0; i < inlist.Getsize(); i++)
            {
                add(inlist.get(i));
            }
        }
    protected:
        T* values;
    private:
        int size;
        int maxSize;
        int nextIndex; //The next available location in the array
        void expandArray()
        {
            T* newArr;
            maxSize = maxSize *2;
            newArr = new T[maxSize];
            for(int i =0; i < nextIndex; i++)
            {
                newArr[i] = values[i];
            }
            delete[] values;

            values = newArr;
        }


};

#endif // ARRAYLIST_H
