// Matthew Mulenga
// mam558
// 11144528

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour {

    Animator anim;

    public GameObject gun;
    public GameObject bullet;


    public float movementSpeed = 3.0f;
    public float rotationSpeed = 150.0f;
    public float bulletSpeed = 10.0f;

    float bulletCooldown = 1.0f;
    float currentCooldown = 0.0f;

    // Use this for initialization
    void Start() {
        anim = GetComponent<Animator>();
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

        if(isShooting && currentCooldown < Time.time) {
            // Match the rotation and orientation of the projectile to the gun.
            // Make the projectile spawn at the origin of the gun, not the player body.
            GameObject newBullet = Instantiate(bullet, gun.transform.position, gun.transform.rotation * Quaternion.Euler(0, 0, -225.00f));

            // Set its velocity
            Rigidbody2D newBulletPhysics = newBullet.GetComponent<Rigidbody2D>();
            newBulletPhysics.velocity = this.transform.right * bulletSpeed;

            // Reset the cooldown of the gun.
            currentCooldown = Time.time + bulletCooldown;
        }
	}

    void die() {
        Destroy(this.gameObject);

        // Reset the game if the player dies
        UnityEngine.SceneManagement.SceneManager.LoadScene(UnityEngine.SceneManagement.SceneManager.GetActiveScene().buildIndex);
    }
}
