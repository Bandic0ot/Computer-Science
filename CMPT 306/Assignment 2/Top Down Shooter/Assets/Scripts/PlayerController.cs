// Matthew Mulenga
// mam558
// 11144528

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PlayerController : MonoBehaviour {

    Animator anim;

    public GameObject gun;
    public GameObject bullet;
    public AudioSource deathSound;

    public float movementSpeed = 3.0f;
    public float rotationSpeed = 150.0f;
    public float bulletSpeed = 10.0f;

    float bulletCooldown = 1.5f;
    float currentCooldown = 0.0f;

    private float minX;
    private float maxX;
    private float minY;
    private float maxY;

    // Use this for initialization
    void Start() {
        anim = GetComponent<Animator>();

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
	void Update() {
        //-------- Movement Mechanics --------
        float xInput = Input.GetAxis("Horizontal");
        float yInput = Input.GetAxis("Vertical");

        this.transform.Rotate(new Vector3(0, 0, -xInput * rotationSpeed * Time.deltaTime));
        this.transform.Translate(Vector2.right * yInput * movementSpeed * Time.deltaTime);

        anim.SetBool("Moving", yInput != 0);

        //-------- Shooting Mechanics --------
        bool isShooting = Input.GetButton("Jump");
        currentCooldown = currentCooldown - Time.deltaTime;

        anim.SetBool("Shooting", isShooting);

        if (isShooting && currentCooldown < Time.time) {
            // Match the rotation and orientation of the projectile to the gun.
            // Make the projectile spawn at the origin of the gun, not the player body.
            GameObject newBullet = Instantiate(bullet, gun.transform.position, gun.transform.rotation * Quaternion.Euler(0, 0, -225.00f));

            // Set its velocity
            Rigidbody2D newBulletPhysics = newBullet.GetComponent<Rigidbody2D>();
            newBulletPhysics.velocity = this.transform.right * bulletSpeed;

            // Reset the cooldown of the gun.
            currentCooldown = Time.time + bulletCooldown;
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

    void die() {
        deathSound.Play();

        Destroy(this.gameObject);

        // Reset the game if the player dies
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
    }
}
