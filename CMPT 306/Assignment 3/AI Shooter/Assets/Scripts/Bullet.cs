using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour {

    Animator anim;

    public GameObject explosion;
	public float damage = 1.0f;

    private float minX;
    private float maxX;
    private float minY;
    private float maxY;

    // Use this for initialization
    void Start () {
        // Camera bounds attribution
        // Modified from answers.unity3d.com/questions/717620/how-to-set-screen-boundaries.html (MikeNewall)
        float cameraDistance = Vector3.Distance(transform.position, Camera.main.transform.position);
        Vector2 bottomCorner = Camera.main.ViewportToWorldPoint(new Vector3(0, 0, cameraDistance));
        Vector2 topCorner = Camera.main.ViewportToWorldPoint(new Vector3(1, 1, cameraDistance));

        minX = bottomCorner.x;
        maxX = topCorner.x;
        minY = bottomCorner.y;
        maxY = topCorner.y;
    }
	
	// Update is called once per frame
	void Update () {

        // Get current position
        Vector3 pos = transform.position;

        // If the bullet crosses the camera bounds destroy it.
        if (pos.x < minX || pos.x > maxX || pos.y < minY || pos.y > maxY ) {
            die();
        }
    }

    private void OnCollisionStay2D(Collision2D collision) {
		collision.gameObject.SendMessage("takeDamage", damage);

        die();
    }

    private void die() {
        Instantiate(explosion, this.transform.position, Quaternion.identity);
        Destroy(this.gameObject);
    }
}
