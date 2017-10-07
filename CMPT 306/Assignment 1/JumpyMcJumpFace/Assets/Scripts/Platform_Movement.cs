// Matthew Mulenga
// mam558
// 11144528

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Platform_Movement : MonoBehaviour {

    public GameObject platform;
    Vector3 currentPosition;

    public float moveSpeed;
    public float positionOffset;
    private float targetPosition;
    private float startPosition;
	private bool reachedEnd;

	// Use this for initialization
	void Start() {
        startPosition = platform.transform.position.x;
		reachedEnd = false;
    }
	
	// Update is called once per frame
	void Update() {
        currentPosition = platform.transform.position;

		Vector3 targetPosition = new Vector3(startPosition + positionOffset, currentPosition.y, currentPosition.z);
		Vector3 reverseTargetPosition = new Vector3(startPosition, currentPosition.y, currentPosition.z);

		// Check to see if the platform position has reached the destination
		// If it has reverse the direction of movement
		if(reachedEnd == false) {
			platform.transform.position = Vector3.MoveTowards (currentPosition, targetPosition, Time.deltaTime * moveSpeed);

			if(currentPosition.x == targetPosition.x) {
				reachedEnd = true;
			}
		} else {
			platform.transform.position = Vector3.MoveTowards (currentPosition, reverseTargetPosition, Time.deltaTime * moveSpeed);

			if(currentPosition.x == startPosition) {
				reachedEnd = false;
			}
		}	  
    }
}