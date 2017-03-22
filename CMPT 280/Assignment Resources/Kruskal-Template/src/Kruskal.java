import lib280.graph.Edge280;
import lib280.graph.Vertex280;
import lib280.graph.WeightedEdge280;
import lib280.graph.WeightedGraphAdjListRep280;
import lib280.tree.ArrayedMinHeap280;

public class Kruskal {
	
	public static WeightedGraphAdjListRep280<Vertex280> minSpanningTree(WeightedGraphAdjListRep280<Vertex280> G) {

		// TODO -- Complete this method.

		// Create a weighted graph with the same vertices as G, but without edges.
		WeightedGraphAdjListRep280 minST = new WeightedGraphAdjListRep280(G.numVertices(), G.directed());
		minST.ensureVertices(G.numVertices());

		UnionFind280 UF = new UnionFind280(G.numVertices());
		ArrayedMinHeap280<WeightedEdge280<Vertex280>> H = new ArrayedMinHeap280<WeightedEdge280<Vertex280>>(G.numEdges() * 2);

		// Store all the edges in a heap.
		for(int i = 1; i <= G.numVertices(); i++) {
			G.eGoFirst(G.vertex(i));
			while(!G.eAfter()) {
				H.insert(G.eItem());

				G.eGoForth();
			}
		}

		for(int i = 1; i < G.numEdges(); i++) {
			int a = H.item().firstItem().index();
			int b = H.item().secondItem().index();

			if(UF.find(a) != UF.find(b)) {
				minST.addEdge(a, b);
				minST.setEdgeWeight(a,b, G.getEdgeWeight(a, b));
				UF.union(a, b);
			}

			H.deleteItem();
		}

		return minST;  // Remove this when you're ready -- it is just a placeholder to prevent a compiler error.
	}
	
	
	public static void main(String args[]) {
		WeightedGraphAdjListRep280<Vertex280> G = new WeightedGraphAdjListRep280<Vertex280>(1, false);
		// If you get a file not found error here and you're using eclipse just remove the 
		// 'Kruskal-template/' part from the path string.
		G.initGraphFromFile("Kruskal-Template/mst.graph");
		System.out.println(G);
		
		WeightedGraphAdjListRep280<Vertex280> minST = minSpanningTree(G);
		
		System.out.println(minST);
	}
}


