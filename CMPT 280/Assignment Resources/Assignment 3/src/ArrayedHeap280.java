import lib280.base.Dispenser280;
import lib280.exception.ContainerEmpty280Exception;
import lib280.exception.ContainerFull280Exception;
import lib280.exception.DuplicateItems280Exception;
import lib280.exception.NoCurrentItem280Exception;
import lib280.tree.ArrayedBinaryTree280;

/**
 * Created by Matt on 2017-01-27.
 */
public class ArrayedHeap280<I extends Comparable<? super I>> extends ArrayedBinaryTree280<I> implements Dispenser280<I> {

    @SuppressWarnings("unchecked")
    public ArrayedHeap280(int cap) {
        super(cap);
        this.items = (I[]) new Comparable[capacity + 1];
    }

    /**
     * Inserts the element x into the heap H.
     * Insert x into H normally, as in ArrayedBinaryTreeWithCursors280<I>
     * @param x item to be inserted into the data structure
     * @throws ContainerFull280Exception If the tree is full currently full.
     * @throws DuplicateItems280Exception Not necessary to implement.
     */
    @Override
    public void insert(I x) throws ContainerFull280Exception, DuplicateItems280Exception {

        // Make sure the container isn't full.
        if(this.isFull()) {
            throw new ContainerFull280Exception("Container is full, cannot insert new element.");
        }

        // If we are inserting into an empty tree we don't need to do any swaps.
        if(this.isEmpty()) {
            this.count++;
            this.items[this.count] = x;
            this.currentNode = 1;
        }

        // If the tree isn't empty we insert in the right most node at the bottom of
        // the tree.
        else {
            this.count++;
            this.currentNode = this.count;
            this.items[this.count] = x;

            // While the currentNode isn't the root we check to see if it's parent
            // is smaller than it.
            while(this.currentNode > 1) {
                if(x.compareTo(this.items[this.findParent(this.currentNode)]) > 0) {
                    I temp = this.items[this.findParent(this.currentNode)];
                    this.items[this.findParent(this.currentNode)] = this.items[this.currentNode];
                    this.items[this.currentNode] = temp;
                }

                // After swapping we set the currentNode to it's parent.
                this.currentNode = this.findParent(this.currentNode);
            }

            // Return the currentNode to the root.
            this.currentNode = 1;
        }
    }

    /**
     * Removes the largest element from the heap H.
     * @throws NoCurrentItem280Exception If the currentNode does not exist.
     */
    @Override
    public void deleteItem() throws NoCurrentItem280Exception {

        // Check to see if the currentNode exists.
        if(!this.itemExists()) {
            throw new NoCurrentItem280Exception("There is no current item.");
        }

        // Replace the root with the last element.
        this.items[this.currentNode] = this.items[this.count];

        // Delete the last element after it has been transferred.
        this.items[this.count] = null;
        this.count--;

        while(this.currentNode < this.count) {
            if(this.items[this.currentNode * 2] != null && this.items[(this.currentNode * 2) + 1] != null) {
                I leftChild = this.items[this.findLeftChild(this.currentNode)];
                I rightChild = this.items[this.findRightChild(this.currentNode)];

                if(leftChild.compareTo(rightChild) > 0) {
                    if(this.items[this.currentNode].compareTo(leftChild) < 0) {
                        I temp = leftChild;
                        leftChild = this.items[this.currentNode];
                        this.items[this.currentNode] = temp;

                        this.currentNode = findLeftChild(this.currentNode);
                    }
                } else if(leftChild.compareTo(rightChild) < 0){
                    if(this.items[this.currentNode].compareTo(rightChild) < 0) {
                        I temp = rightChild;
                        rightChild = this.items[this.currentNode];
                        this.items[this.currentNode] = temp;

                        this.currentNode = findRightChild(this.currentNode);
                    }
                } else
                    this.currentNode = this.count;

            } else if(this.items[this.currentNode * 2] != null) {
                I leftChild = this.items[this.findLeftChild(this.currentNode)];

                if(this.items[this.currentNode].compareTo(leftChild) < 0) {
                    I temp = leftChild;
                    leftChild = this.items[this.currentNode];
                    this.items[this.currentNode] = temp;

                    this.currentNode = findLeftChild(this.currentNode);
                } else
                    this.currentNode = this.count;
            } else if(this.items[(this.currentNode * 2) + 1] != null) {
                I rightChild = this.items[this.findRightChild(this.currentNode)];

                if(this.items[this.currentNode].compareTo(rightChild) < 0) {
                    I temp = rightChild;
                    rightChild = this.items[this.currentNode];
                    this.items[this.currentNode] = temp;

                    this.currentNode = findRightChild(this.currentNode);
                } else
                    this.currentNode = this.count;
            }
        }

        this.currentNode = 1;
    }

    // Regression Tests
    public static void main(String args[]) {

        Exception x = null;

        // Test the creation of a new heap.
        ArrayedHeap280 heap = new ArrayedHeap280(10);
        if(!heap.isEmpty()) {
            System.out.println("Test of isEmpty() on an empty heap failed.");
        }

        // Test deleteItem() on an empty heap.
        x = null;
        try {
            heap.deleteItem();
        } catch (NoCurrentItem280Exception e) {
            x = e;
        } finally {
            if(x == null) {
                System.out.println("Expected an exception deleting from an empty heap.");
            }
        }

        // Test insert() on an empty heap.
        heap.insert(10);

        if(!heap.itemExists()) {
            System.out.println("Test of insert() on an empty heap failed.");
        }

        // Test deleteItem() on a heap with a single element.
        heap.deleteItem();

        if(heap.itemExists()) {
            System.out.println("Test of deleteItem() on a heap with a single element failed.");
        }

        // Test insert() on a heap with multiple elements
        heap.insert(11);
        heap.insert(8);
        heap.insert(12);

        if(!heap.items[1].equals(12) ||
                !heap.items[2].equals(8) ||
                !heap.items[3].equals(11)) {
            System.out.println("Test of insert() on a heap with multiple elements failed.");
        }

        // Test delete() on a heap with multiple elements
        heap.deleteItem();
        heap.deleteItem();
        heap.deleteItem();

        // Test delete() on an empty heap.
        x = null;

        try {
            heap.deleteItem();
        } catch(NoCurrentItem280Exception e) {
            x = e;
        } finally {
            if(x == null) {
                System.out.println("Expected an exception deleting from an empty heap.");
            }
        }

        // Test insert() multiple times after deleting
        for(int i = 1; i < 11; i++) {
            heap.insert(i);
        }

        if(heap.count != 10 || !heap.items[5].equals(8)) {
            System.out.println("Test of insert() multiple times on a heap that has been deleted from failed.");
        }

        // Test delete() on a "large" heap.
        heap.deleteItem();

        System.out.println(heap.toString());

        System.out.println("Regression test complete.");

    }
}
