using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Model : MonoBehaviour {

	public int minRooms;
	public int maxRooms;

	public int roomMinWidth;
	public int roomMinHeight;
	public int roomMaxWidth;
	public int roomMaxHeight;

	public int dungeonMinWidth;
	public int dungeonMinHeight;
	public int dungeonMaxWidth;
	public int dungeonMaxHeight;

	private GameObject[][] dungeonModel;
	private GameObject map;

	void Start() {
		map = new GameObject("Map");
		dungeonModel = new GameObject[Random.Range(roomMinWidth, roomMaxWidth)][Random.Range(roomMinHeight, roomMaxHeight)];
	}

	void SpawnRoom() {

	}

	void Digger() {

	}

	void InitializeMap(GameObject[][] model) {
		for(int i = 0; i < dungeonModel.Length; i++) {
			for(int j = 0; j < dungeonModel[i].Length; j++) {
				Vector3 position = new Vector3(i, j, 0.0f);

				GameObject tile = new GameObject();
				tile.transform.position = position;

				dungeonModel[i][j] = tile;

				tile.transform.parent = map.transform;
			}
		}
	}
}
