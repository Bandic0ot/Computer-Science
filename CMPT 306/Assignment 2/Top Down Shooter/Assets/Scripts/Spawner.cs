using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spawner : MonoBehaviour {

	public GameObject zombie;

	public Transform[] spawnLocation;
	public float spawnCooldown = 5.0f;

	float currentCooldown = 0.0f;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		currentCooldown = currentCooldown - Time.deltaTime;

		if (currentCooldown < Time.time) {
			// Select random location for zombie to spawn from.

			int locationIndex = Random.Range (0, spawnLocation.Length);

			// Spawn a zombie.
			Instantiate(zombie, spawnLocation[locationIndex].position, Quaternion.identity);

			// Reset the spawn cooldown.
			currentCooldown = Time.time + spawnCooldown;
		}
	}
}
