using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Zombie : MonoBehaviour {

	public GameObject target;
	public AudioSource deathSound;

	Animator anim;
	UIManager manager;
	Vector3 spawnPoint;
	DecisionTree root;

	public float health = 3.0f;
	public float damage = 1.0f;
	public float movementSpeed = 1.0f;
	public float threatRange = 4.0f;
	public float attackRange = 2.0f;
	public float allyRange = 4.0f;
	public float spawnRange = 3.0f;
	public float healthThreshold = 2.0f;

	// Use this for initialization
	void Start () {
		spawnPoint = this.transform.position;
		target = GameObject.Find("Player");
		deathSound = AudioSource.FindObjectOfType<AudioSource>();
		manager = FindObjectOfType<UIManager>();
		anim = this.GetComponent<Animator>();

		buildDecisionTree();
	}

	// Update is called once per frame
	void Update () {
		root.search(root);
	}

	/* ------- Decision Methods ------- */
	// Check to see if the target is within the threat zone.
	public bool insideThreatRange() {
		Debug.Log("Deciding threat range.");
		if (Vector2.Distance(this.transform.position, target.transform.position) < threatRange) {
			return true;
		}

		return false;
	}

	// Check to see if the target is within attack range.
	public bool insideAttackRange() {
		Debug.Log("Deciding attack range.");
		if (Vector2.Distance(this.transform.position, target.transform.position) < attackRange) {
			return true;
		}

		return false;
	}

	// Check to see if there are allies nearby.
	public bool alliesNear() {
		Debug.Log("Deciding ally range.");
		if (Vector2.Distance(this.transform.position, target.transform.position) < allyRange) {
			return true;
		}

		return false;
	}

	// Check to see if HP is too low.
	public bool hpLow() {
		Debug.Log("Deciding HP level.");
		if (health < healthThreshold) {
			return true;
		}

		return false;
	}

	// Check to see if entity is too far from spawn.
	public bool tooFarFromSpawn() {
		Debug.Log("Deciding spawn range.");
		if (Vector2.Distance(this.transform.position, this.spawnPoint) > spawnRange) {
			return true;
		}

		return false;
	}

	// Perform a random action.
	public bool randomDecision() {
		Debug.Log("Deciding random.");
		float randomNumber = Random.value;

		if(randomNumber <= 0.5) {
			return true;
		}

		return false;
	}

	/* ------- Action Methods ------- */
	// Attack the target.
	public void attack() {
		Debug.Log("Attacking.");
		this.transform.position = Vector3.MoveTowards(this.transform.position, target.transform.position, movementSpeed * 2.0f * Time.deltaTime);
	}

	// Move away from the target.
	public void retreat() {
		Debug.Log("Retreating.");
		this.transform.position = Vector3.MoveTowards(this.transform.position, target.transform.position, -movementSpeed * Time.deltaTime);
	}

	// Move closer to the target.
	public void advance() {
		Debug.Log("Advancing.");
		this.transform.position = Vector3.MoveTowards(this.transform.position, target.transform.position, movementSpeed * Time.deltaTime);
	}

	// Move towards spawn.
	public void moveToSpawn() {
		Debug.Log("Moving to spawn.");
		this.transform.position = Vector3.MoveTowards(this.transform.position, this.spawnPoint, movementSpeed * Time.deltaTime);
	}

	// Walk in a random direction.
	public void randomWalk() {
		Debug.Log("Walking.");
		float randomX = Random.Range(-1.0f, 1.0f);
		float randomY = Random.Range(-1.0f, 1.0f);

		this.transform.position = Vector3.MoveTowards(this.transform.position, new Vector3(randomX * 5, randomY * 5, 0), movementSpeed * Time.deltaTime);
	}

	// Perform idle animation.
	public void idleAnimation() {
		Debug.Log("Idling.");

		anim.Play("Zombie_Idle");
	}

	private void OnCollisionStay2D(Collision2D collision) {
		if (collision.gameObject.tag == "Player")
		{
			collision.gameObject.SendMessage("die");
		}
	}

	private void takeDamage(float damage) {
		this.health = this.health - this.damage;

		if(health <= 0) {
			this.die();
		}
	}

	private void die() {
		manager.SendMessage("addKill");
		Destroy(this.gameObject);

		deathSound.Play();
	}

	public void buildDecisionTree() {
		// Set all the action nodes.
		DecisionTree attackActionNode = new DecisionTree();
		DecisionTree retreatActionNode = new DecisionTree();
		DecisionTree advanceActionNode = new DecisionTree();
		DecisionTree moveToSpawnActionNode = new DecisionTree();
		DecisionTree randomWalkActionNode = new DecisionTree();
		DecisionTree idleActionNode = new DecisionTree();

		attackActionNode.setActionDelegate(attack);
		retreatActionNode.setActionDelegate(retreat);
		advanceActionNode.setActionDelegate(advance);
		moveToSpawnActionNode.setActionDelegate(moveToSpawn);
		randomWalkActionNode.setActionDelegate(randomWalk);
		idleActionNode.setActionDelegate(idleAnimation);

		// Set all the decision nodes.
		DecisionTree threatRangeDecisionNode = new DecisionTree();
		DecisionTree attackRangeDecisionNode = new DecisionTree();
		DecisionTree tooFarFromSpawnDecisionNode = new DecisionTree();
		DecisionTree alliesNearDecisionNode = new DecisionTree();
		DecisionTree hpLow1DecisionNode = new DecisionTree();
		DecisionTree randomDecisionNode = new DecisionTree();
		DecisionTree hpLow2DecisionNode = new DecisionTree();

		threatRangeDecisionNode.setDecisionDelegate(insideThreatRange);
		attackRangeDecisionNode.setDecisionDelegate(insideAttackRange);
		tooFarFromSpawnDecisionNode.setDecisionDelegate(tooFarFromSpawn);
		alliesNearDecisionNode.setDecisionDelegate(alliesNear);
		hpLow1DecisionNode.setDecisionDelegate(hpLow);
		randomDecisionNode.setDecisionDelegate(randomDecision);
		hpLow2DecisionNode.setDecisionDelegate(hpLow);

		// Build tree structure breadth-first.
		threatRangeDecisionNode.setLeftNode(attackRangeDecisionNode);
		threatRangeDecisionNode.setRightNode(tooFarFromSpawnDecisionNode);

		attackRangeDecisionNode.setLeftNode(alliesNearDecisionNode);
		attackRangeDecisionNode.setRightNode(hpLow1DecisionNode);

		tooFarFromSpawnDecisionNode.setLeftNode(moveToSpawnActionNode);
		tooFarFromSpawnDecisionNode.setRightNode(randomDecisionNode);

		alliesNearDecisionNode.setLeftNode(attackActionNode);
		alliesNearDecisionNode.setRightNode(hpLow2DecisionNode);

		hpLow1DecisionNode.setLeftNode(retreatActionNode);
		hpLow1DecisionNode.setRightNode(advanceActionNode);

		randomDecisionNode.setLeftNode(randomWalkActionNode);
		randomDecisionNode.setRightNode(idleActionNode);

		hpLow2DecisionNode.setLeftNode(retreatActionNode);
		hpLow2DecisionNode.setRightNode(attackActionNode);

		root = threatRangeDecisionNode;
	}
}
