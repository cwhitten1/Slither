#ifndef ARRAYLIST_H
#define ARRAYLIST_H

template <class T>
class ArrayList
{
    public:
        ArrayList(){values = new T[40];nextIndex = 0;size = 40;}
        virtual ~ArrayList(){delete[] values;}
        int Getsize() { return size; }
        int GetnextIndex() { return nextIndex; }
        void add(T val)
            {if(nextIndex == size)
                    expandArray();
             values[nextIndex] = val;nextIndex++;} //Add to end of list
        T get(int index){return values[index];}
        void set(int index, T val){values[index] = val;}
    protected:
        T* values;
    private:
        int size;
        int nextIndex; //The next available location in the array
        T* newArr;
        void expandArray()
        {
            newArr = new T[size *2];
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
