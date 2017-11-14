// Matthew Mulenga
// mam558
// 11144528

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DecisionTree {
	/* -------- Instance Variables -------- */
	public delegate bool Decision();
	public delegate void Action();

	DecisionTree leftNode;
	DecisionTree rightNode;
	Decision decision;
	Action action;

	/* -------- Constructor ------- */
	public DecisionTree() {
		this.leftNode = null;
		this.rightNode = null;
		this.decision = null;
		this.action = null;
	}

	/* -------- Methods ------- */
	public void setLeftNode(DecisionTree tree) {
		this.leftNode = tree;
	}

	public void setRightNode(DecisionTree tree) {
		this.rightNode = tree;
	}

	public void setDecisionDelegate(Decision d) {
		this.decision = d;
	}

	public void setActionDelegate(Action a) {
		this.action = a;
	}

	public void search(DecisionTree tree) {
		if(tree.action != null) {
			tree.action();
		}

		if(tree.decision != null) {
			if (tree.decision()) {
				search(tree.leftNode);
			} else {
				search(tree.rightNode);
			}
		}
	}
}
