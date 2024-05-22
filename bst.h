#include "mybinarytree.h"
#include <algorithm>

class BST {
	BinaryTree* tree = new MyBinaryTree();

	public:
	bool search(int num) {
		return search_node(tree->getRoot(), num);
	}

	bool search_node(node* n, int num) {
		if (n == NULL) {
			return false;
		}
		if (n->elem == num) {
			return true;
		}
		if (num > n->elem) {
			// proceed to right
			return search_node(n->right, num);
		} else {
			return search_node(n->left, num);
		}
	}

    node* search1(int num) {
        return searchNode(tree->getRoot(), num);
    }

    node* searchNode(node* n, int num) {
        if (n == NULL) {
            return nullptr;
        }
        if (n->elem == num) {
            return n;
        }
        if (num > n->elem) {
            return searchNode(n->right, num);
        } else {
            return searchNode(n->left, num);
        }
    }

    // TODO perform post-processing by checking for violation after insertion
    // from the node inserted (or from its parent) until the root
	node* insert(int num) {
		node* n = tree->getRoot();
		if (n == NULL) {
			return tree->addRoot(num);
		}
        
		node* nodeInserted =  insert_node(n, num);
        checkAll(nodeInserted);

        return nodeInserted;
	}

	node* insert_node(node* n, int num) {
		if (n == NULL) {
			return NULL;
		}
		if (n->elem == num) {
			return NULL;
		}
		if (num > n->elem) {
			if (!n->right) {
				return tree->addRight(n, num);
			} else {
				return insert_node(n->right, num);
			}
		} else {
			if (!n->left) {
				return tree->addLeft(n, num);
			} else {
				return insert_node(n->left, num);
			}
		}
	}


    // TODO perform post-processing by checking for violation after deletion
    // from the parent of the node removed until the root
    bool remove(int num) {
        node* nodeRemovedParent = search1(num)->parent;
        bool isRemoved = remove_node(tree->getRoot(), num);
        checkAll1(nodeRemovedParent);
        
        return isRemoved;
    }

	bool remove_node(node* n, int num) {
		if (n == NULL) {
			return false;
		}
		if (n->elem == num) {
            if (n->left && n->right) {
                node* r = n->right;
                while (r->left) {
                    r = r->left;
                }
                node* rpar = r->parent;
                int rem = tree->remove(r);
                n->elem = rem;
                checkAll1(rpar);
            } else {
    			tree->remove(n);
            }
            return true;
		}
		if (num > n->elem) {
			return remove_node(n->right, num);
		} else {
			return remove_node(n->left, num);
		}
	}

    // TODO copy and paste your completed restructure method here
    bool restructure(node* gp) {
        node* par; // parent
        // TODO find parent
        int leftHeight;
        int rightHeight;

        leftHeight = (gp->left) ? gp->left->height() : 0;
        
        rightHeight = (gp->right) ? gp->right->height() : 0;

        par = (rightHeight > leftHeight) ? gp->right : gp->left;
        
        // This is an indicator of the placement of grandparent to parent (gtop)
        bool gtop_right = false;
        if (gp->right == par) {
            gtop_right = true;
        }

        node* child;
        // TODO find child
        int leftHeightC;
        int rightHeightC;

        leftHeightC = (par->left) ? par->left->height() : 0;

        rightHeightC = (par->right) ? par->right->height() : 0;

        if(leftHeightC == rightHeightC) {
            if (gtop_right && par->right) {
                child = par->right;
            }else if (gtop_right && !par->right) {
                child = par->left;
            }

            if (!gtop_right && par->left) {
                child = par->left;
            }else if (!gtop_right && !par->left) {
                child = par->right;
            }
        }else if (leftHeightC > rightHeightC) {
            child = par->left;
        }else {
            child = par->right;
        }
        
        // This is an indicator of the placement of parent to child (ptoc)
        bool ptoc_right = false;
        if (par->right == child) {
            ptoc_right = true;
        }

        // FOR THE FOLLOWING: Write in each of the if statements a console output
        // on its corresponding operation (ZIGLEFT, ZIGRIGHT, ZIGZAGLEFT, or ZIGZAGRIGHT)

        // z
        //  \
        //   y
        //    \
        //     x
        if (gtop_right && ptoc_right) {
            // TODO call to either zigleft or zigright or both
            zigleft(par);
            cout << "ZIGLEFT" << endl;
        }

        // z
        //   \
        //     y
        //    /
        //   x
        else if (gtop_right && !ptoc_right) {
            // TODO call to either zigleft or zigright or both
            zigright(child);
            zigleft(child);
            cout << "ZIGZAGLEFT" << endl;
        }

        //     z
        //    /
        //   y
        //  /
        // x
        else if (!gtop_right && !ptoc_right) {
            // TODO call to either zigleft or zigright or both
            zigright(par);
            cout << "ZIGRIGHT" << endl;
        }

        //      z
        //    /
        //  y
        //   \
        //    x
        else {
            // TODO call to either zigleft or zigright or both
            zigleft(child);
            zigright(child);
            cout << "ZIGZAGRIGHT" << endl;
        }

        return true;
    }

    void zigleft(node* curr) {
        tree->zigleft(curr);
    }

    void zigright(node* curr) {
        tree->zigright(curr);
    }

	void print() {
		tree->print();
	}

    void checkAll(node *p) {
        node* dummyNode = p;
        bool found = false;
        node* violationNode = nullptr;
        
        while (!found && dummyNode) {
            found = checkViolation(dummyNode->parent);
            dummyNode = dummyNode->parent;
        }

        violationNode = dummyNode;
        bool check = false;

        // The grandparent with violation if found
        if (violationNode) {
            check = restructure(violationNode);
        }
    }

    void checkAll1(node *p) {
        node* dummyNode = p;
        bool found = false;
        node* violationNode = nullptr;

        while (!found && dummyNode) {
            found = checkViolation(dummyNode);
            if (dummyNode->parent && !found) {
                dummyNode = dummyNode->parent;
            }
            
            if (dummyNode == tree->getRoot()) {
                if (checkViolation(dummyNode)) {
                    found = true;
                }else {
                    dummyNode = nullptr;
                }
            }
            
            /*if (dummyNode) {
                cout << dummyNode->elem << endl;
            }else {
                cout << "NO DUMMY NODE!" << endl;
            }*/
        }

        violationNode = dummyNode;
        bool check = false;

        // The node with violation if found
        if (violationNode) {
            check = restructure(violationNode);
        }
    }

    bool checkViolation(node* p) {
        if (!p) {
            return false;
        }

        int leftHeight = (p->left) ? p->left->height() : 0;
        int rightHeight = (p->right) ? p->right->height() : 0;
        int gap = 0;

        if (rightHeight == leftHeight) {
            return false;
        }

        // cout << leftHeight << " " << rightHeight << endl;

        gap = abs(rightHeight - leftHeight);

        if (gap >= 2) {
            return true;
        }
        return false;
    }
};