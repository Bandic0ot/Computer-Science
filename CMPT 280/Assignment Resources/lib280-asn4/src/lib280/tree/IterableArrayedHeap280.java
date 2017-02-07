package lib280.tree;

public class IterableArrayedHeap280<I extends Comparable<? super I>> extends ArrayedHeap280<I>  {

	/**
	 * Create an iterable heap with a given capacity.
	 * @param cap The maximum number of elements that can be in the heap.
	 */
	public IterableArrayedHeap280(int cap) {
		super(cap);
	}

	// TODO
	// Add iterator() and deleteAtPosition() methods here.

	/**
	 * Deletes the specified item at the given iterator.
	 * @param iter - An iterator containing a heap.
	 */
	public void deleteAtPosition(ArrayedBinaryTreeIterator280<I> iter) {
		if(iter.tree.count() > 1) {
			iter.currentNode = 1;
			iter.tree.items[iter.tree.currentNode] = iter.tree.items[iter.tree.count];
		}
		iter.tree.count--;

		// If we deleted the last remaining item, make the the current item invalid, and we're done.
		if( iter.tree.count == 0) {
			iter.tree.currentNode = 0;
			return;
		}

		// Propagate the new root down the lib280.tree.
		int n = 1;

		// While offset n has a left child...
		while( findLeftChild(n) <= iter.tree.count ) {
			// Select the left child.
			int child = findLeftChild(n);

			// If the right child exists and is larger, select it instead.
			if( child + 1 <= iter.tree.count && iter.tree.items[child].compareTo(iter.tree.items[child+1]) < 0 )
				child++;

			// If the parent is smaller than the root...
			if( iter.tree.items[n].compareTo(iter.tree.items[child]) < 0 ) {
				// Swap them.
				I temp = iter.tree.items[n];
				iter.tree.items[n] = iter.tree.items[child];
				iter.tree.items[child] = temp;
				n = child;
			}
			else return;

		}
	}

	/**
	 * Creates and returns a new ArrayedBinaryTreeIterator object.
	 * @return A new ArrayedBinaryTreeIterator called iter.
	 */
	public ArrayedBinaryTreeIterator280<I> iterator() {
		ArrayedBinaryTreeIterator280<I> iter = new ArrayedBinaryTreeIterator280<>(this);

		return iter;
	}
	
}
