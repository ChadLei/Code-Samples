/*
DIRECTIONS:

Implement insert and delete in a modified-binary search tree of integers.
This search tree is much like a binary search tree, but with 3 child nodes for each parent
instead of 2 (left: value less than parents, middle: value equal to parents, right: value greater than parents)
Delete only 1 node per delete method call.

INPUT / OUTPUT EXAMPLES:

Example 1: 
insert 5,4,9,5,7,2,2    -> 2,2,4,5,5,7,9 

Example 2:
insert 7,10,10
delete 10				-> 7,10

*/

import java.io.IOException;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.util.*;
// No other imports are permitted

// The following definitions of Tree and Node are provided.
// insert and delete will be methods of class Tree.

public class Tree {
    private class Node {
        private int val;
        private Node left = null;
        private Node right = null;
        private Node mid = null;

        public Node(int val) {
            this.val = val;
        }
    }

    private Node root;


    /* 
     * Please complete this method.
     * Inserts val into the tree.
     */
    public void insert(int val) {
        if (root == null) root = new Node(val);
        else {
            Node current = root;
            while (current != null){
                if (val < current.val){
                    if (current.left == null) {
                        current.left = new Node(val);
                        break;
                    }
                    else {current = current.left;}
                } 
                else if (val == current.val){
                    if (current.mid == null) {
                        current.mid = new Node(val);
                        break;
                    }
                    else {current = current.mid;}
                }
                else if (val > current.val){
                    if (current.right == null) {
                        current.right = new Node(val);
                        break;
                    }
                    else {current = current.right;}
                }
            }
        }
    }

    /* 
     * Please complete this method.
     * Deletes only one instance of val from the tree.
     * If val does not exist in the tree, do nothing.
     */
    public void delete(int val) {
        if (root == null) return; // tree is empty
        else if (root.val == val && root.left == null && root.mid == null && root.right == null) root = null;
        else {
            Node current = root;
            while (current != null){
                // Case 0: one child (left)
                if (val < current.val) {
                    Node temp = current.left;
                    if (val == temp.val && temp.left == null && temp.mid == null && temp.right == null) {
                        current.mid = temp = null;
                        break;
                    }
                    else current = temp;
                }
                
                // Case 1: one child (mid)
                else if (val == current.val) {
                    Node temp = current.mid;
                    if (val == temp.val && temp.left == null && temp.mid == null && temp.right == null) {
                        current.mid = temp = null;
                        break;
                    }
                    else current = temp;
                }
                
                // Case 2: one child (right)
                else if (val > current.val) {
                    Node temp = current.right;
                    if (val == temp.val && temp.left == null && temp.mid == null && temp.right == null) {
                        current.right = temp = null;
                        break;
                    }
                    else current = temp;
                }                
            }
        }
    }