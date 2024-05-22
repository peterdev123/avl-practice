#include "mybinarytree.h"

class BST {
	BinaryTree* tree = new MyBinaryTree();

	public:
	bool search(int num) {
        node* searched_node = search_node(tree->getRoot(), num);
		if (searched_node != NULL) {
            splay(searched_node);
        }else {
            return false;
        }
	}

	node* search_node(node* n, int num) {
		if (n == NULL) {
			return NULL;
		}
		if (n->elem == num) {
			return n;
		}
		if (num > n->elem) {
			// proceed to right
			return search_node(n->right, num);
		} else {
			return search_node(n->left, num);
		}
	}

	node* insert(int num) {
		node* n = tree->getRoot();
		if (n == NULL) {
			return tree->addRoot(num);
		}
        node* inserted_node = insert_node(n, num);
        search(num);
		return inserted_node;
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

    bool remove(int num) {
        search(num);
        node* removed = remove_node(tree->getRoot(), num);
        if (removed->right) {
            search(searchLeftMost(removed->right));
        }else {
            return false;
        }
    }

    int searchLeftMost(node *n) {
        node* curr = n;
        if (curr->left) {
            curr = curr->left;
        }else {
            return curr->elem;
        }
    }

	node* remove_node(node* n, int num) {
		if (n == NULL) {
			return NULL;
		}
		if (n->elem == num) {
            if (n->left && n->right) {
                node* r = n->right;
                while (r->left) {
                    r = r->left;
                }
                int rem = tree->remove(r);
                n->elem = rem;
            } else {
    			tree->remove(n);
            }
            return n;
		}
		if (num > n->elem) {
			return remove_node(n->right, num);
		} else {
			return remove_node(n->left, num);
		}
	}
    // GIVEN the grandparent (or z), find the parent (or y), and the child (or x).
    bool restructure(node* gp) {
        node* par; // parent
        // TODO find parent
        int leftHeight = 0;
        int rightHeight = 0;

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
        int leftHeightC = 0;
        int rightHeightC = 0;

        leftHeightC = (par->left) ? par->left->height() : 0;

        rightHeightC = (par->right) ? par->right->height() : 0;

        if(leftHeightC == rightHeightC) {
            if(gp->left) {
                if(par == gp->left) {
                    leftHeightC++;
                }
            } else if(gp->right) {
                rightHeightC++;
            }
        }

        child = (leftHeightC > rightHeightC) ? par->left : par->right;
        
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

    void splay(node* n) {
        while (n != tree->getRoot()) {
            node* par = n->parent;
            node* gp = par->parent;

            if (!gp) {
                if(par->right == n) {
                    zigleft(n);
                }else {
                    zigright(n);
                }
                break;
            }

            bool gtop_right = false;
            if (gp->right == par) {
                gtop_right = true;
            }

            bool ptop_right = false;
            if (par->right == n) {
                ptop_right = true;
            }

            //For ZIGZIGLEFT
            if (gtop_right && ptop_right) {
                zigleft(par);
                zigleft(n);
            }

            //For ZIGZAGLEFT
            if (gtop_right && !ptop_right) {
                zigright(n);
                zigleft(n);
            }

            //For ZIGZIGRIGHT
            if (!gtop_right && !ptop_right) {
                zigright(par);
                zigright(n);
            }

            //For ZIGZAGRIGHT
            if (!gtop_right && ptop_right) {
                zigleft(n);
                zigright(n);
            }
        } 
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
};