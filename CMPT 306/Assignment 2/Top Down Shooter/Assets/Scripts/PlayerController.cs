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


    public float movement_speed = 3.0f;
    public float rotation_speed = 150.0f;
    public float bullet_speed = 10.0f;

    float bullet_cooldown = 1.0f;
    float cur_bullet_cooldown = 0.0f;

    // Use this for initialization
    void Start () {
        anim = GetComponent<Animator>();
	}
	
	// Update is called once per frame
	void Update () {
        //-------- Movement Mechanics --------
        float xInput = Input.GetAxis("Horizontal");
        float yInput = Input.GetAxis("Vertical");

        this.transform.Rotate(new Vector3(0, 0, -xInput * rotation_speed * Time.deltaTime));
        this.transform.Translate(Vector2.right * yInput * movement_speed * Time.deltaTime);

        anim.SetBool("Moving", yInput != 0);

        //-------- Shooting Mechanics --------
        bool is_shooting = Input.GetButton("Jump");
        cur_bullet_cooldown -= Time.deltaTime;

        if (is_shooting && cur_bullet_cooldown < Time.time) {
            // Match the rotation and orientation of the projectile to the gun.
            // Make the projectile spawn at the origin of the gun, not the player body.
            GameObject newly_created_bullet = Instantiate(bullet, gun.transform.position, gun.transform.rotation * Quaternion.Euler(0, 0, -225.00f));

            // Set its velocity
            Rigidbody2D new_bullet_physics = newly_created_bullet.GetComponent<Rigidbody2D>();
            new_bullet_physics.velocity = this.transform.right * bullet_speed;

            // Record when we shot the gun.
            cur_bullet_cooldown = Time.time + bullet_cooldown;
        }
	}

    public void die()
    {
        Destroy(this.gameObject);

        // Reset the game if the player dies
        UnityEngine.SceneManagement.SceneManager.LoadScene(UnityEngine.SceneManagement.SceneManager.GetActiveScene().buildIndex);
    }
}
