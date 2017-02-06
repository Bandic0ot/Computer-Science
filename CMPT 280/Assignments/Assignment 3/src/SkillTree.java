import lib280.list.LinkedList280;
import lib280.tree.BasicMAryTree280;

public class SkillTree extends BasicMAryTree280<Skill> {

	/**	
	 * Create lib280.tree with the specified root node and
	 * specified maximum arity of nodes.  
	 * @timing O(1) 
	 * @param x item to set as the root node
	 * @param m number of children allowed for future nodes 
	 */
	public SkillTree(Skill x, int m) {

		super(x,m);
	}

	/**
	 * A convenience method that avoids typecasts.
	 * Obtains a subtree of the root.
	 * 
	 * @param i Index of the desired subtree of the root.
	 * @return the i-th subtree of the root.
	 */
	public SkillTree rootSubTree(int i) {
		return (SkillTree)super.rootSubtree(i);
	}

	public LinkedList280<Skill> skillDependencies(String name) {
		LinkedList280<Skill> skillList = new LinkedList280<>();

		return skillDependenciesHelper(name, skillList);
	}

	protected LinkedList280<Skill> skillDependenciesHelper(String name, LinkedList280<Skill> skillList) {
		if(this.rootItem().getSkillName().equals(name)) {
			return skillList;
		} else {
			SkillTree clone = this.rootSubTree(this.rootLastNonEmptyChild());

			skillList.insert(clone.rootItem());
			return clone.skillDependenciesHelper(name, skillList);
		}
	}

	public static void main(String args[]) {

		// Create all the skills.
		Skill jump = new Skill("Jump", "Allows the hero to jump into the air.", 1);
		Skill doubleJump = new Skill("Double Jump", "Allows the hero to jump again once in the air.", 2);
		Skill dodge = new Skill("Dodge", "Allows the hero to quickly dodge sideways.", 2);
		Skill hover = new Skill("Hover", "Allows the hero to slow descent after a long fall.", 3);
		Skill roll = new Skill("Roll", "Allows the hero to roll in any direction.", 4);
		Skill backFlip = new Skill("Back Flip", "Allows the hero to perform a back flip.", 5);
		Skill tripleJump = new Skill("Triple Jump", "Allows the hero to jump twice while in the air.", 7);
		Skill glide = new Skill("Glide", "Allows the hero to glide over a distance of 15m.", 8);
		Skill superJump = new Skill("Super Jump", "Allows the hero to jump 20m into the air.", 10);
		Skill fly = new Skill("Fly", "Allows the hero to fly for 100m.", 15);

		// Create all the trees.
		SkillTree jumpTree = new SkillTree(jump, 3);
		SkillTree dodgeTree = new SkillTree(dodge, 3);
		SkillTree doubleJumpTree = new SkillTree(doubleJump, 3);
		SkillTree hoverTree = new SkillTree(hover, 3);
		SkillTree backFlipTree = new SkillTree(backFlip, 3);
		SkillTree rollTree = new SkillTree(roll, 3);
		SkillTree tripleJumpTree = new SkillTree(tripleJump, 3);
		SkillTree glideTree = new SkillTree(glide, 3);
		SkillTree superJumpTree = new SkillTree(superJump, 3);
		SkillTree flyTree = new SkillTree(fly, 3);

		// Set all the subtrees.
		hoverTree.setRootSubtree(glideTree, 1);
		glideTree.setRootSubtree(flyTree, 1);

		doubleJumpTree.setRootSubtree(tripleJumpTree, 1);
		tripleJumpTree.setRootSubtree(superJumpTree, 1);

		dodgeTree.setRootSubtree(backFlipTree, 1);
		dodgeTree.setRootSubtree(rollTree, 2);

		jumpTree.setRootSubtree(dodgeTree, 1);
		jumpTree.setRootSubtree(doubleJumpTree, 2);
		jumpTree.setRootSubtree(hoverTree, 3);

		System.out.println(jumpTree.skillDependencies("Fly").toString());
		System.out.println(jumpTree.toStringByLevel());
	}
	

}
