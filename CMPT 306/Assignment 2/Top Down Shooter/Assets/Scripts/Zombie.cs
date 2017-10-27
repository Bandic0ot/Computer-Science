// Matthew Mulenga
// mam558
// 11144528

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Zombie : MonoBehaviour
{
    public GameObject target;
    public AudioSource deathSound;

    UIManager manager;

    public float movement_speed = 1.5f;
    public float damage = 1.0f;

    // Use this for initialization
    void Start()
    {
        target = GameObject.Find("Player");
        deathSound = AudioSource.FindObjectOfType<AudioSource>();
        manager = FindObjectOfType<UIManager>();
    }

    // Update is called once per frame
    void Update()
    {
        if (target)
        {
            this.transform.position = Vector3.MoveTowards(this.transform.position, target.transform.position, movement_speed * Time.deltaTime);
        }
    }

    private void OnCollisionStay2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Player")
        {
            collision.gameObject.SendMessage("die");
        }

        if (collision.gameObject.tag == "Bullet")
        {
            die();
        }
    }

    public void die()
    {
        manager.SendMessage("addKill");
        Destroy(this.gameObject);

        deathSound.Play();
    }

	public void spawn() {
		
	}
}
