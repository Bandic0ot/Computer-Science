// Matthew Mulenga
// mam558
// 11144528

/* Threshold Parameters
 * threatRange: 4 
 * - Chosen because it let's the player move around the 
 * map without immediately getting spotted.
 * 
 * attackRange: 3 
 * - Chosen because it let's the player get close enough to 
 * the zombie that they can still get away when it attacks (since it's movement 
 * speed when attacking is doubled).
 * 
 * allyRange: 2
 * - Chosen because the zombies should be fairly close (not touching) to detect
 * an ally, thus enabling them to attack. If this was increased they'd be able
 * to attack while their health is low too often.
 * 
 * spawnRange: 5
 * - Chosen because I wanted the zombies to be able to reach the centre (where 
 * the player spawns), but not be able to go all the way across the map.
 * 
 * healthThreshold: 1
 * - Chosen because I want the zombie to have minimal health before it starts
 * deciding to run from the player.
 */

// NOTE: Debug.Logs can be uncommented to test to see which decisions or 
// actions are being performed.

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Zombie : MonoBehaviour {

	public GameObject target;
	public AudioSource deathSound;

	Animator anim;
	UIManager manager;
	DecisionTree root;
	Vector3 spawnPoint;
	Vector3 randomPosition;
	GameObject[] allies;

	public float health = 3.0f;
	public float movementSpeed = 1.0f;
	public float threatRange = 4.0f;
	public float attackRange = 2.0f;
	public float allyRange = 4.0f;
	public float spawnRange = 3.0f;
	public float healthThreshold = 2.0f;
	public float timer = 5.0f;

	private float minX;
	private float maxX;
	private float minY;
	private float maxY;

	bool actionLock = true;
	bool walking = false;

	// Use this for initialization
	void Start () {
		spawnPoint = this.transform.position;
		target = GameObject.Find("Player");
		deathSound = AudioSource.FindObjectOfType<AudioSource>();
		manager = FindObjectOfType<UIManager>();
		anim = this.GetComponent<Animator>();

		// Camera bounds attribution
		// Modified from answers.unity3d.com/questions/717620/how-to-set-screen-boundaries.html (MikeNewall)
		float cameraDistance = Vector3.Distance(transform.position, Camera.main.transform.position);
		Vector2 bottomCorner = Camera.main.ViewportToWorldPoint(new Vector3(0, 0, cameraDistance));
		Vector2 topCorner = Camera.main.ViewportToWorldPoint(new Vector3(1, 1, cameraDistance));

		minX = bottomCorner.x;
		maxX = topCorner.x;
		minY = bottomCorner.y;
		maxY = topCorner.y;

		buildDecisionTree();
	}

	// Update is called once per frame
	void Update () {
		root.search(root);

		// Since Time.deltaTime can't be updated repeatedly, inside our randomWalk() function 
		// (since it's locked), we move it out to update and set a flag within the randomWalk() 
		// function which indicates whether or not our zombie should be walking.
		// There's probably a waaaayyyyy easier way of doing this.
		if(walking) {
			this.transform.position = Vector3.MoveTowards(this.transform.position, randomPosition, movementSpeed * Time.deltaTime);
		}

		// Get current position
		Vector3 pos = transform.position;

		// If the player crosses the cameras edge set their position to the edge
		// ie. Keep the player within the screen
		if (pos.x < minX) pos.x = minX;
		if (pos.x > maxX) pos.x = maxX;
		if (pos.y < minY) pos.y = minY;
		if (pos.y > maxY) pos.y = maxY;

		this.transform.position = pos;
	}

	void FixedUpdate() {
		allies = GameObject.FindGameObjectsWithTag("Enemy");
	}

	/* ------- DECISION METHODS ------- */
	// Check to see if the target is within the threat zone.
	public bool insideThreatRange() {
		//Debug.Log("Deciding threat range.");

		if (Vector2.Distance(this.transform.position, target.transform.position) < threatRange) {
			return true;
		}

		return false;
	}

	// Check to see if the target is within attack range.
	public bool insideAttackRange() {
		//Debug.Log("Deciding attack range.");

		if (Vector2.Distance(this.transform.position, target.transform.position) < attackRange) {
			return true;
		}

		return false;
	}

	// Check to see if there are allies nearby.
	public bool alliesNear() {
		//Debug.Log("Deciding ally range.");

		for(int i = 0; i < allies.Length; i++) {
			if(allies[i] != this.gameObject) {
				if (Vector2.Distance(this.transform.position, allies[i].transform.position) < allyRange) {
					return true;
				}
			}
		}

		return false;
	}

	// Check to see if HP is too low.
	public bool hpLow() {
		//Debug.Log("Deciding HP level.");

		if (health <= healthThreshold) {
			return true;
		}

		return false;
	}

	// Check to see if entity is too far from spawn.
	public bool tooFarFromSpawn() {
		//Debug.Log("Deciding spawn range.");

		if (Vector2.Distance(this.transform.position, this.spawnPoint) > spawnRange) {
			return true;
		}

		return false;
	}

	// Perform a random action.
	public bool randomDecision() {
		//Debug.Log("Deciding random.");

		float randomNumber = Random.value;

		if(randomNumber <= 0.5) {
			return true;
		}

		return false;
	}

	/* ------- ACTION METHODS ------- */
	// Attack the target.
	public void attack() {
		//Debug.Log("Attacking.");

		this.transform.position = Vector3.MoveTowards(this.transform.position, target.transform.position, movementSpeed * 2.0f * Time.deltaTime);

		anim.Play("Zombie_Walking");
	}

	// Move away from the target.
	public void retreat() {
		//Debug.Log("Retreating.");

		this.transform.position = Vector3.MoveTowards(this.transform.position, target.transform.position, -movementSpeed * Time.deltaTime);

		anim.Play("Zombie_Walking");
	}

	// Move closer to the target.
	public void advance() {
		//Debug.Log("Advancing.");

		this.transform.position = Vector3.MoveTowards(this.transform.position, target.transform.position, movementSpeed * Time.deltaTime);

		anim.Play("Zombie_Walking");
	}

	// Move towards spawn.
	public void moveToSpawn() {
		//Debug.Log("Moving to spawn.");

		this.transform.position = Vector3.MoveTowards(this.transform.position, this.spawnPoint, movementSpeed * Time.deltaTime);

		anim.Play("Zombie_Walking");
	}

	// Walk in a random direction.
	public void randomWalk() {
		if(actionLock) {
			//Debug.Log("Walking.");

			// This lock keeps the update from repeatedly calling the randomWalk() or idle animation 
			// if one of them is currently running.
			actionLock = false;

			// Create a random point to walk to.
			float randomX = Random.Range(this.transform.position.x - 100, this.transform.position.x + 100);
			float randomY = Random.Range(this.transform.position.y - 100, this.transform.position.y + 100);
			randomPosition = new Vector3(randomX, randomY, 0);

			walking = true;

			anim.Play("Zombie_Walking");

			// The timer specifies how long the function should execute for before releasing a lock.
			// This is what happens when 332 takes over your life. :(
			Invoke("releaseActionLock", timer);
		}
	}

	// Perform idle animation.
	public void idleAnimation() {
		if(actionLock) {
			//Debug.Log("Idling.");

			actionLock = false;

			// Don't do anything, just play the idle animation.
			anim.Play("Zombie_Idle");

			Invoke("releaseActionLock", timer);
		}
	}
		
	private void releaseActionLock() {
		actionLock = true;

		// Need to reset this so the zombie won't keep walking.
		walking = false;
	}

	private void OnCollisionStay2D(Collision2D collision) {
		if (collision.gameObject.tag == "Player")
		{
			collision.gameObject.SendMessage("die");
		}
	} 

	private void takeDamage(float damage) {
		this.health = this.health - damage;

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
