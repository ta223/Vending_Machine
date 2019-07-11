#pragma once
#include <stdlib.h>

template <typename class_type>
class Linker {	//links one node to another

public:
	class_type *next;
	class_type *prev;

};

template<typename class_type>
class LinkedList {

public:
	LinkedList(class_type *initial_node) : first_node(NULL), n_nodes(0), last_node(NULL) {

		first_node = (class_type *)malloc(sizeof(class_type));
		if(first_node == NULL) {/*Dont forget to handle this exception*/}
		n_nodes++;
		*first_node = *initial_node;
		first_node->next = NULL;
		first_node->prev = NULL;
		last_node = first_node;

	}

	/*Adds a node at the end of the list*/
	void AddNode(class_type* new_object) {

		last_node->next = (class_type *)malloc( sizeof(class_type));
		if (last_node->next == NULL) {/*Dont forget to handle this exception*/}
		*(last_node->next) = *new_object;
		n_nodes++;

		last_node->next->prev = last_node;
		last_node = last_node->next;
		last_node->next = NULL;
		
	}

	/*deletes the last node*/
	void DeleteNode() {

		class_type *temp = last_node;
		if(last_node->prev != NULL) last_node = last_node->prev;
		if(temp != NULL) free(temp);
		last_node->next = NULL;
		n_nodes--;

	}

	int n_nodes;	//number of nodes
	class_type *first_node, *last_node;

};

