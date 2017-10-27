using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraScript : MonoBehaviour {

	float cameraWidth;
	float cameraHeight;

	public Transform[] boundary;

	// Use this for initialization
	void Start () {
		float cameraHeight = Camera.main.orthographicSize * 2;
		float cameraWidth = Camera.main.aspect * cameraHeight;
		Vector2 cameraSize = new Vector2(cameraWidth, cameraHeight);
	}
	
	// Update is called once per frame
	void Update () {

	}
}
