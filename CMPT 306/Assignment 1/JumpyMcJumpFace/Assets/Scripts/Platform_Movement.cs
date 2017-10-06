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

	// Use this for initialization
	void Start () {
        startPosition = platform.transform.position.x;
    }
	
	// Update is called once per frame
	void Update () {
        currentPosition = platform.transform.position;
        Vector3 targetPosition = new Vector3(startPosition + positionOffset, platform.transform.position.y, platform.transform.position.z);
        Vector3 reverseTargetPosition = new Vector3(startPosition, platform.transform.position.y, platform.transform.position.z);

        if(platform.transform.position.x != startPosition) {
            platform.transform.position = Vector3.MoveTowards(currentPosition, reverseTargetPosition, Time.deltaTime * moveSpeed);
        } else if (platform.transform.position != targetPosition) {
            platform.transform.position = Vector3.MoveTowards(currentPosition, targetPosition, Time.deltaTime * moveSpeed);
        }
        
    }
}
