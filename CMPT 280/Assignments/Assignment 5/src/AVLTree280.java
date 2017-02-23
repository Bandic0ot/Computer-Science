import lib280.base.Dispenser280;
import lib280.base.Searchable280;
import lib280.exception.ContainerEmpty280Exception;
import lib280.exception.ContainerFull280Exception;
import lib280.exception.DuplicateItems280Exception;
import lib280.exception.NoCurrentItem280Exception;
import lib280.tree.BinaryNode280;
import lib280.tree.LinkedSimpleTree280;
import lib280.tree.OrderedSimpleTree280;

/**
 * Created by Matt on 2017-02-16.
 */
public class AVLTree280<I extends Comparable<? super I>> extends OrderedSimpleTree280<I> {
    // -------- Instance Variables --------
    /**
     * An integer to store the height of the current node.
     */
    protected int leftSubtreeHeight;
    protected int rightSubtreeHeight;

    // -------- Constructor --------

    /**
     * Sets the inherited instance variable 'rootNode' to null.
     * And set the initial heights of the trees.
     */

    public AVLTree280() {
        super();

        leftSubtreeHeight = 0;
        rightSubtreeHeight = 0;
    }

    // -------- Methods --------
    @Override
    public void insert(I x) {
        if(isEmpty()) {
            rootNode = createNewNode(x);
        } else if(x.compareTo(rootItem()) < 0) {
            AVLTree280<I> leftTree = (AVLTree280<I>) rootLeftSubtree();
            leftTree.insert(x);
            setRootLeftSubtree(leftTree);

            // Recompute the subtree height
            leftSubtreeHeight = Integer.max(leftTree.leftSubtreeHeight, leftTree.rightSubtreeHeight) + 1;

        } else {
            AVLTree280<I> rightTree = (AVLTree280<I>) rootRightSubtree();
            rightTree.insert(x);
            setRootRightSubtree(rightTree);

            // Recompute the subtree height
            rightSubtreeHeight = Integer.max(rightTree.leftSubtreeHeight, rightTree.rightSubtreeHeight) + 1;
        }

        restoreAVLProperty();
    }

    @Override
    public void deleteItem() throws NoCurrentItem280Exception {

    }

    public void restoreAVLProperty() {
        // Left Rotation (Uses recursion)
        if(rightSubtreeHeight - leftSubtreeHeight == 2) {
            rotateLeft();
            //restoreAVLProperty();
        }
        // Right Rotation

        // Double Left Rotation

        // Double Right Rotation
    }

    private void rotateLeft() {
        AVLTree280<I> temp = (AVLTree280<I>) rootLeftSubtree();
        temp.insert(rootItem());

        setRootLeftSubtree(temp);

        temp = (AVLTree280<I>) rootRightSubtree();
        insert(temp.rootItem());
//        temp.clear();
//        temp.rootNode.setLeftNode(rootNode);

        //temp.insert(cur.rightNode().item());


//        setRootRightSubtree(null);
    }

    private void rotateRight() {

    }

    @Override
    public void clear() {
        super.clear();
        leftSubtreeHeight = 0;
        rightSubtreeHeight = 0;
    }


    public static void main(String args[]) {
        AVLTree280<Integer> T = new AVLTree280<>();

        T.insert(8);
        T.insert(10);
        T.insert(11);

        System.out.println(T.toStringByLevel());
        System.out.println("Left: " + T.leftSubtreeHeight + " Right: " + T.rightSubtreeHeight);
    }
}
