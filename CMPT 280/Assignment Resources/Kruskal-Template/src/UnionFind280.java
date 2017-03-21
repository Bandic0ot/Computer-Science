

import lib280.graph.Edge280;
import lib280.graph.GraphAdjListRep280;
import lib280.graph.Vertex280;
import lib280.graph.WeightedGraphAdjListRep280;


public class UnionFind280 {
	GraphAdjListRep280<Vertex280, Edge280<Vertex280>> G;
	
	/**
	 * Create a new union-find structure.
	 * 
	 * @param numElements Number of elements (numbered 1 through numElements, inclusive) in the set.
	 * @postcond The structure is initialized such that each element is in its own subset.
	 */
	public UnionFind280(int numElements) {
		G = new GraphAdjListRep280<Vertex280, Edge280<Vertex280>>(numElements, true);
		G.ensureVertices(numElements);		
	}
	
	/**
	 * Return the representative element (equivalence class) of a given element.
	 * @param id The elements whose equivalence class we wish to find.
	 * @return The representative element (equivalence class) of the element 'id'.
	 */
	public int find(int id) {
		// TODO - Write this method
		int x = id;

		// Go to the first edge of the designated vertex.
		G.eGoFirst(G.vertex(x));

		// Check if the edge exists and if it has an outgoing edge to the next vertex
		while(G.eItemExists() && G.isAdjacent(x, G.eItemAdjacentIndex())) {
			x = G.eItemAdjacentIndex();
			G.eGoFirst(G.vertex(x));
		}
		
		return x;
	}
	
	/**
	 * Merge the subsets containing two items, id1 and id2, making them, and all of the other elemnets in both sets, "equivalent".
	 * @param id1 First element.
	 * @param id2 Second element.
	 */
	public void union(int id1, int id2) {
		// TODO - Write this method.

		if(find(id1) == find(id2)) {
			return;
		}

		G.addEdge(id1, id2);
	}

	public static void main(String args[]) {
		UnionFind280 U = new UnionFind280(8);

		U.union(1, 2);

		if(U.find(1) !=  2) {
			System.out.println("Error: Something went wrong in the union() method.");
		}

		U.union(3, 2);
		U.union(7, 3);
		U.union(4, 6);
		U.union(6, 5);

		if(U.find(7) !=  2) {
			System.out.println("Error: Something went wrong in the union() method.");
		}

		U.union(5, 2);

		// Using the same subsets found in the assignment outline, test the find() method.
		for(int i = 1; i <= 7; i++) {
			if(U.find(i) != 2) {
				System.out.println("Error: Something went wrong in the find() method.");
			}
		}

	}
	
	
}
