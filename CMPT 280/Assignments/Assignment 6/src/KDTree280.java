import lib280.base.NDPoint280;
import lib280.base.Searchable280;
import lib280.exception.NoCurrentItem280Exception;
import lib280.tree.BinaryNode280;
import lib280.tree.LinkedSimpleTree280;

/**
 * Created by Matt on 2017-03-07.
 */
public class KDTree280<I extends Comparable<? super I>> extends LinkedSimpleTree280<I> {

    /**	The current node as set by search. */
    protected NDPoint280[] array;

    public KDTree280(int size) {
        array = new NDPoint280[size];
    }

    protected KDNode280<I> createNewNode(I point) {
        return new KDNode280<I>(point);
    }

    protected KDTree280<I> createKDTree(NDPoint280[] pointArray, int left, int right, int depth, int dimension) {
        if(pointArray == null) {
            return null;
        } else {
            int d = depth % dimension;
            int medianOffset = (left + right) / 2;

            //jSmallest(pointArray, left, right, d, medianOffset);
        }

        return null;
    }

    protected int partition(I[] points, int left, int right, int d) {

        I pivot = points[right];

        int swapOffset = left;
        for(int i = left; i < right; i++) {

            if(points[i].compareTo(pivot) <= 0) {

                I temp = points[i];
                points[i] = points[swapOffset];
                points[swapOffset] = temp;

                swapOffset = swapOffset + 1;
            }
        }

        I temp = points[right];
        points[right] = points[swapOffset];
        points[swapOffset] = temp;

        return swapOffset;
    }

    protected void jSmallest(I[] list, int left, int right, int j, int d) {
        if(right > left) {

            int pivotIndex = partition(list, left, right, d);

            if(j < pivotIndex) {

                jSmallest(list, left, pivotIndex - 1, j, d);

            } else if(j > pivotIndex) {

                jSmallest(list, right, pivotIndex + 1, j, d);
            }
        }

    }



    public static void main(String args[]) {
        NDPoint280 NDPoint1 = new NDPoint280(2);
        NDPoint280 NDPoint2 = new NDPoint280(2);
        NDPoint280 NDPoint3 = new NDPoint280(2);
        NDPoint280 NDPoint4 = new NDPoint280(2);
        NDPoint280 NDPoint5 = new NDPoint280(2);

        Double[] point1 = {1.0,2.0};
        Double[] point2 = {3.0,4.0};
        Double[] point3 = {5.0,6.0};
        Double[] point4 = {7.0,8.0};
        Double[] point5 = {9.0,10.0};

        NDPoint1.setPoint(point1);
        NDPoint2.setPoint(point2);
        NDPoint3.setPoint(point3);
        NDPoint4.setPoint(point4);
        NDPoint5.setPoint(point5);

        NDPoint280[] array = new NDPoint280[5];

        array[0] = NDPoint1;
        array[1] = NDPoint2;
        array[2] = NDPoint3;
        array[3] = NDPoint4;
        array[4] = NDPoint5;

        for(int i = 0; i < 5; i++) {
            System.out.println(array[i].toString());
        }

        KDTree280<NDPoint280> T = new KDTree280<NDPoint280>(5);
        T.array =

        int test = T.partition(array, 0, 2, 2);
        System.out.println(test);
    }
}
