//
//  Sequence.h
//  Project 2
//
//  Created by Kim Svatos on 4/15/15.
//  Copyright (c) 2015 Kim Svatos. All rights reserved.
//

#ifndef __Project_2__Sequence__
#define __Project_2__Sequence__
#include <string>
typedef std::string ItemType;



class Sequence
{
    
public:
    Sequence();
    ~Sequence();
    Sequence(const Sequence& other);
    Sequence& operator=(const Sequence& rhs);
    
    
    bool empty() const;
    int size() const;
    bool insert(int pos, const ItemType& value);
    bool insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    
    
    
    
    
private:
    
    struct Node
    {
    public:
        ItemType m_data;
        Node* next;
        Node* previous;
    };
    
    Node* head;
    int m_size;
    
};


int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);


#endif /* defined(__Project_2__Sequence__) */
