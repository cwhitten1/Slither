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
        void removeAll(){delete[] values;}
    protected:
        T* values;
    private:
        int size;
        int maxSize;
        int nextIndex; //The next available location in the array
        T* newArr;
        void expandArray()
        {
            maxSize = maxSize *2;
            newArr = new T[maxSize];
            for(int i =0; i < nextIndex; i++)
            {
                newArr[i] = values[i];
            }
            delete[] values;

            values = newArr;
            delete[] newArr;
        }


};

#endif // ARRAYLIST_H
