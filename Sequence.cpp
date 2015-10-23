//
//  Sequence.cpp
//  Project 2
//
//  Created by Kim Svatos on 4/15/15.
//  Copyright (c) 2015 Kim Svatos. All rights reserved.
//

#include "Sequence.h"

Sequence::Sequence()
{
    head = nullptr;   //archetype empty sequence
    m_size = 0;
}

bool Sequence::empty() const
{
    if (head == nullptr)
        return true;
    
    else return false;
}

int Sequence::size() const
{
    return m_size;
}


bool Sequence::insert(int pos, const ItemType& value)
{
    
    if(head == nullptr && pos == 0) //if EMPTY and its FIRST INSERTED
    {
        Node* inserted = new Node;
        head = inserted;
        inserted->next = nullptr;
        inserted->previous = nullptr;
        inserted->m_data = value;
        m_size++;
        return true;
    }
    
    if(head == nullptr && pos != 0) //this is a bad call to the function
    {
        return false;
    }
    
    
    if(head != nullptr && pos == size()) //inserted LAST in existing list
    {
        Node* pointer;
        for(pointer = head; pointer->next != nullptr; pointer = pointer->next)
            ; // pointer should point to CURRENT last one in list
        
        Node* inserted = new Node; //make new node
        inserted->previous = pointer; //previous should be FORMER last one
        inserted->next = nullptr; //inserted 'next' points to nullptr
        pointer->next = inserted; //previous last one points to inserted
        inserted->m_data = value;
        m_size++;
        return true;
        
    }
    
    if( head != nullptr && pos < size()) //in MIDDLE of already existing list
    {
        
        Node* pointer = head;
        
        
        for(int counter = 0; counter < pos; counter++) //get pointer to point to where you want to insert
            pointer = pointer->next;
        
        Node* inserted = new Node; //make a new Node and set its value
        inserted->m_data = value;
        
        
        inserted->previous = pointer->previous; //give inserted appropriate 'previous'
        inserted->next = pointer; //inserted 'next' is where we left 'pointer'
        
        if(pointer->previous != nullptr) //if not first in list
        {
            pointer->previous->next = inserted; //make BEFORE one link to it
            pointer->previous = inserted; //make AFTER one  link to it
        }
        
        else //this must mean inserted is first so make head point to it
        {
            head = inserted;
            pointer->previous = inserted;
        }
        
        
        m_size++;
        return true;
    }
    
    return false;
}


bool Sequence::insert(const ItemType& value)
{
    
    if(head == nullptr) //if no sequence, this is first in sequence!
    {
        Node* inserted = new Node;
        head = inserted;
        inserted->next = nullptr;
        inserted->previous = nullptr;
        inserted->m_data = value;
        m_size++;
        return true;
    }
    
    if(head != nullptr)
    {
        Node* pointer;
        for(pointer = head; pointer->next != nullptr;  pointer = pointer-> next) //will stop at current last
        {
            if(value <= pointer->m_data) //where pointer points will be AFTER what we insert
            {
                
                Node* inserted = new Node;
                inserted->next = pointer; //set new values, no stomping
                
                
                if(pointer->previous == nullptr) //must be inserted first then
                {
                    inserted->previous = nullptr;
                    pointer->previous = inserted;
                    head = inserted;
                }
                else //not first so can follow pointer->previous
                {
                    inserted->previous = pointer->previous;
                    pointer->previous->next = inserted;
                    pointer->previous = inserted;
                }
                
                inserted->m_data = value;
                m_size++;
                return true;
            }
            
            
        } //if get to this point it must be last
        
        Node* inserted = new Node; //make new node
        inserted->previous = pointer; //previous should be FORMER last one
        inserted->next = nullptr; //end points to nullptr
        pointer->next = inserted; //former last NEXT is new last, aka inserted
        
        inserted->m_data = value;
        m_size++;
        
        
    }
    return true;
}


bool Sequence::erase(int pos)
{
    
    if(head != nullptr && pos < m_size)      //check that we wont follow nullptr
    {
        Node* pointer = head;
        for(int k = 0; k != pos; k++)
        {
            if(pointer->next != nullptr)
                pointer = pointer->next;         //advance until point to Node we want
        }
        
        if(pos == 0)                         //if wants to delete FIRST
        {
            if(size() == 1)                  //if only one in sequence
            {
                delete pointer;
                head = nullptr;
                m_size--;
                return true;
            }
            else                             //if first but NOT only one in sequence
            {
                head = pointer->next;        //set head to next one in series, head's previous to null
                
                
                //changed 5:19
                if(head != nullptr)
                    head->previous = nullptr;
                
                
                
                
                
                delete pointer;
                m_size--;
                return true;
            }
            
        }
        
        if(pos == size()-1)                          //if LAST in sequence
        {
            pointer->previous->next = nullptr;       //make second to last point to null, then delete last
            delete pointer;
            m_size--;
            return true;
        }
        
        //MIDDLE Of long sequence
        
        
        Node* before = pointer->previous; //holds node BEFORE one deleted
        Node* after = pointer-> next; //holds node AFTER one deleted
        
        before->next = pointer->next;        //connect nodes on either side of that erased
        after->previous = pointer->previous;
        delete pointer;
        
        m_size--;
        return true;
    }
    
    else return false;
    
}



int Sequence::remove(const ItemType& value)
{
    int removedCount = 0;
    Node* pointer;
    if(head != nullptr) //check that there's something to remove
    {
        int position = 0;
        for(pointer = head; pointer != nullptr; )
        {
            
            
            if(pointer->m_data == value) //when find the value, erase it
            {
                pointer = pointer->next;   //advance first so our pointer isnt' dangling
                erase(position);
                
                
                removedCount++;
                
                
            }
            else
            {
                position++;                 //keeps track of what pos to call for erase()
                pointer = pointer->next;    //if dont find anything, advance to next
            }
        }
    }
    return removedCount;
}


bool Sequence::get(int pos, ItemType& value) const
{
    if(pos >= m_size || pos<0) //check that it's a valid call
        return false;
    if(head == nullptr)  //check that there is a sequence;
        return false;
    
    
    Node* pointer=head;
    for(int k = 0; k<pos; k++)  //advance until we get to the pos we want
    {
        if(pointer != nullptr)
            pointer=pointer->next;
    }
    
    value = pointer->m_data;    //assign its data to value;
    
    return true;
}



bool Sequence::set(int pos, const ItemType& value)
{
    
    if(pos >= m_size || pos<0) //check that its a valid request
        return false;
    if(head == nullptr)
        return false;
    
    
    Node* pointer=head;
    for(int k = 0; k<pos; k++) //increment pointer until gets to node position we want
    {
        if(pointer != nullptr)
            pointer=pointer->next;
    }
    
    pointer->m_data = value; //set data member
    
    return true;
}

int Sequence::find(const ItemType& value) const
{
    
    if(head == nullptr) //check that there IS a list
        return -1;
    
    int position = -1;
    for(Node* pointer = head; pointer != nullptr; pointer = pointer->next)
    {
        position++;
        if(pointer->m_data == value)
            return position;
    }
    
    return -1;
}


void Sequence::swap(Sequence& other)
//remember must take same number of steps!!!
{
    Node* holder = head; //holds this head so we don't lose it
    int rSize = m_size;
    
    head = other.head;
    m_size = other.m_size;
    other.head = holder;
    other.m_size = rSize;  //trade pointers and exchange sizes
    
}
/////////////////////////////////////
//          house keeping
/////////////////////////////////////


Sequence::~Sequence()
{
    Node* pointer=head;
    for(int k = 0; k<m_size; k++) //do this "size" times
    {
        erase(0);
        pointer = head;
    }
}


Sequence::Sequence(const Sequence& other)
{
    
    if(other.head == nullptr)
    {
        m_size = 0;
        head = nullptr;
        return;
    }
    
    
    Node* rPointer = other.head;
    
    
    head = new Node;
    head->previous = nullptr;
    head->next = nullptr;
    m_size = 1;
    head->m_data = rPointer->m_data;
    
    if(rPointer->next != nullptr)
        rPointer = rPointer->next;
    
    for(int k = 1; k<other.size(); k++)
    {
        insert(k, rPointer->m_data); //assign pos in our sequences to match pos in other sequence
        
    }
    m_size = other.size();
    
}


Sequence& Sequence::operator=(const Sequence& rhs)
{
    if(this != &rhs)
    {
        Sequence a(rhs);
        swap(a);
    }
    return *this;
}

int subsequence(const Sequence& seq1, const Sequence& seq2)

{
    if(seq1.empty() || seq2.empty()) //if empty, return -1
        return -1;
    
    ItemType value1, value2;
    seq2.get(0, value2); //whats the first value in seq2?
    if(seq1.find(value2) == -1) //if start of seq2 isnt even in seq1, return -1
        return -1;
    
    
    int pos;
    for(pos = seq1.find(value2); pos < seq1.size(); pos++)
        //pos holds first possible start of subsequence, start there
    {
        for(int k = 0; k < seq2.size(); k++) //go through seq2 to check for matching in seq1
        {
            seq1.get(pos + k, value1);
            seq2.get(k, value2);
            if(value1==value2)
            {
                if(k == seq2.size() - 1) //if equal and last one in seq2, return starting pos!
                    return pos;
                else
                    continue;           //if equal, keep checking that they STAY equal
            }
            else break;         //if not equal, increment seq1, start trying to match up again
            
        }
    }
    return -1;
}


void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    if(seq1.size() == 0) //if either is empty, set it to the other, non-empty one.
    {
        result = seq2;
        return;
    }
    else
        if (seq2.size() == 0)
        {
            result = seq2;
            return;
        }
    
    Sequence z;
    result = z; //effectively "empties" result
    
    
    ItemType value1;
    ItemType value2;
    
    int resultPos;
    int k = 0;
    for(resultPos = 0; resultPos < (seq1.size() + seq2.size()); )
    {
        if(k < seq1.size())
        {
            seq1.get(k, value1);    //is there anything left to insert from seq1?
            result.insert(resultPos, value1);
            resultPos++;            //only increment resultPos if we insert something
        }
        if(k < seq2.size())  //is there anything left to insert from seq2?
        {
            seq2.get(k, value2);
            result.insert(resultPos, value2);
            resultPos++;            //only increment resultPos if we insert something
        }
        k++;    //move to next pos in seq1 and seq2
    }
    
}
