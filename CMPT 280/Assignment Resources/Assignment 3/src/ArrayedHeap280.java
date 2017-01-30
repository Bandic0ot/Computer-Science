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
     *
     * @param x item to be inserted into the data structure
     * @throws ContainerFull280Exception
     * @throws DuplicateItems280Exception
     */
    @Override
    public void insert(I x) throws ContainerFull280Exception, DuplicateItems280Exception {
        if(this.isFull()) {
            throw new ContainerFull280Exception("Container is full, cannot insert new element.");
        }

        if(this.isEmpty()) {
            this.currentNode++;
            this.items[this.currentNode] = x;
            this.count++;
        } else {
            while (this.itemExists()) {
                this.currentNode++;
            }
            this.currentNode++;
            this.items[this.currentNode] = x;
            this.count++;

            while (x.compareTo(this.items[this.findParent(this.currentNode)]) > 0) {
                I temp = this.items[this.findParent(this.currentNode)];
                this.items[this.findParent(this.currentNode)] = this.items[this.currentNode];
                this.items[this.currentNode] = temp;

                this.currentNode = this.currentNode / 2;
            }
        }
    }

    /**
     * Removes the largest element from the heap H.
     * @throws NoCurrentItem280Exception
     */
    @Override
    public void deleteItem() throws NoCurrentItem280Exception {
        if(!this.itemExists()) {
            throw new NoCurrentItem280Exception("There is no current item.");
        }
    }

    // Regression Tests
    public static void main(String args[]) {

        Exception x = null;

        // Test the creation of a new heap.
        ArrayedHeap280 heap = new ArrayedHeap280(10);
        if(!heap.isEmpty()) {
            System.out.println("Test of isEmpty() on empty heap failed.");
        }

        // Test deleteItem() on an empty tree.
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

        // Test insert() on an empty tree.
        heap.insert(10);

        if(!heap.itemExists()) {
            System.out.println("Test of insert() on empty tree failed.");
        }

        // Test deleteItem() on a tree with a single element.
        heap.deleteItem();

        if(heap.itemExists()) {
            System.out.println("Test of deleteItem() on a tree with a single element failed.");
        }

        System.out.println(heap.toString());

        System.out.println("Regression test complete.");

    }
}
