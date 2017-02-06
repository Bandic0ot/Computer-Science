import lib280.base.Dispenser280;
import lib280.exception.ContainerEmpty280Exception;
import lib280.exception.ContainerFull280Exception;
import lib280.exception.DuplicateItems280Exception;
import lib280.exception.NoCurrentItem280Exception;
import lib280.tree.ArrayedBinaryTree280;

/**
 * Created by Matthew Mulenga on 2017-01-27.
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
            int difference;

            // Check to see if the currentNode has two children.
            if(this.items[this.findLeftChild(this.currentNode)] != null &&
                    this.items[this.findRightChild(this.currentNode)] != null) {

                // If it does, figure out which child is larger.
                difference = this.items[this.findLeftChild(this.currentNode)].compareTo
                        ((this.items[this.findRightChild(this.currentNode)]));

                // If the left child is larger compare it to the currentNode.
                if(difference > 0 && this.items[this.currentNode].compareTo
                        (this.items[findLeftChild(this.currentNode)]) < 0) {

                    // If the currentNode is smaller swap it with the left child.
                    I temp = this.items[this.findLeftChild(this.currentNode)];
                    this.items[this.findLeftChild(this.currentNode)] = this.items[this.currentNode];
                    this.items[this.currentNode] = temp;

                    // Set the currentNode to the child that was just swapped.
                    this.currentNode = this.findLeftChild(this.currentNode);
                }

                // If the right child is larger compare it to the currentNode.
                else if(difference < 0 && this.items[this.currentNode].compareTo
                        (this.items[findRightChild(this.currentNode)]) < 0) {

                    // If the currentNode is smaller swap it with the right child.
                    I temp = this.items[this.findRightChild(this.currentNode)];
                    this.items[this.findRightChild(this.currentNode)] = this.items[this.currentNode];
                    this.items[this.currentNode] = temp;

                    // Set the currentNode to the child that was just swapped.
                    this.currentNode = this.findRightChild(this.currentNode);
                }

                // If neither of the children exist or are not larger than the currentNode
                // we exit the loop.
                else {
                    this.currentNode = this.count;
                }
            }

            // Check to see if the currentNode has only one child. (This will be on the left.)
            else if(this.items[this.findLeftChild(this.currentNode)] != null) {

                // If it does, compare the child with the currentNode.
                if (this.items[this.currentNode].compareTo(this.items[findLeftChild(this.currentNode)]) < 0) {

                    // If the currentNode is smaller swap it with the child.
                    I temp = this.items[this.findLeftChild(this.currentNode)];
                    this.items[this.findLeftChild(this.currentNode)] = this.items[this.currentNode];
                    this.items[this.currentNode] = temp;

                    // Set the currentNode to the child that was just swapped.
                    this.currentNode = this.findLeftChild(this.currentNode);
                } else {

                    // If the child is smaller than the currentNode we don't swap
                    // and exit the loop.
                    this.currentNode = this.count;
                }
            }

            // If there are no children exit the loop.
            else {
                this.currentNode = this.count;
            }
        }

        // Return the currentNode to the root.
        this.currentNode = 1;
    }

    // Regression Tests
    public static void main(String args[]) {

        Exception x = null;

        // Test the creation of a new heap.
        ArrayedHeap280 heap = new ArrayedHeap280(10);

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
        if(heap.count != 9 || !heap.items[5].equals(3)) {
            System.out.println("Test of deleteItem() on a large heap failed.");
        }

        // Test delete() on the entire heap.
        for(int i = 0; i < 9; i++) {
            heap.deleteItem();
        }

        if(heap.itemExists()) {
            System.out.println("Test of deleteItem() on entire heap failed.");
        }

        System.out.println("Regression test complete.");

    }
}

