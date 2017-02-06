import lib280.base.LinearIterator280;
import lib280.exception.AfterTheEnd280Exception;
import lib280.exception.ContainerEmpty280Exception;
import lib280.exception.NoCurrentItem280Exception;
import lib280.tree.ArrayedBinaryTreePosition280;

/**
 * Created by Matt on 2017-02-06.
 */
public class ArrayedBinaryTreeIterator280 extends ArrayedBinaryTreePosition280 implements LinearIterator280{

    @Override
    public boolean before() {
        return false;
    }

    @Override
    public Object item() throws NoCurrentItem280Exception {
        return null;
    }

    @Override
    public boolean after() {
        return false;
    }

    @Override
    public boolean itemExists() {
        return false;
    }

    @Override
    public void goForth() throws AfterTheEnd280Exception {

    }

    @Override
    public void goFirst() throws ContainerEmpty280Exception {

    }

    @Override
    public void goBefore() {

    }

    @Override
    public void goAfter() {

    }
}
