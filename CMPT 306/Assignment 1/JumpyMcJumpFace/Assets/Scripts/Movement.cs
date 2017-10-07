// Matthew Mulenga
// mam558
// 11144528

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Movement : MonoBehaviour {

    Rigidbody2D body;
    Animator anim;
	Vector3 startPosition;

	public Transform groundCheck;
	public LayerMask groundType;
    public float jumpForce;
    public float moveForce;

    public float maxSpeed = 10.0f;
    bool facingRight = true;
    bool isGrounded = false;
    float groundCheckRadius = 0.2f;

    // Use this for initialization
    void Start () {
        body = GetComponent<Rigidbody2D>();
        anim = GetComponent<Animator>();

		startPosition = body.transform.position;
	}

	// Update is called once per frame
	void Update () {
		bool jump = Input.GetButtonDown ("Jump");

        if (jump) {
            if (isGrounded) {
                body.AddForce(new Vector2(0, jumpForce));
            }
        }
    }

    void FixedUpdate() {
        isGrounded = Physics2D.OverlapCircle(groundCheck.position, groundCheckRadius, groundType);
        float moveX = Input.GetAxis("Horizontal");

		anim.SetFloat("Speed", Mathf.Abs(moveX));
		anim.SetBool("Ground", isGrounded);

		// Cap the player's horizontal speed. 
        body.AddForce(new Vector2(moveX * moveForce, 0));
		if (Mathf.Abs(body.velocity.x) > maxSpeed) {
			if (body.velocity.x > 0) {
				body.velocity = new Vector2 (maxSpeed, body.velocity.y);
			} else if (body.velocity.x < 0) {
				body.velocity = new Vector2 (-maxSpeed, body.velocity.y);
			}
		}

		// Flip the character if they change directions.
        if (moveX > 0 && !facingRight) {
            Flip();
        } else if(moveX < 0 && facingRight) {
            Flip();
        }
    }

    void Flip() {
        facingRight = !facingRight;

        Vector2 bodyScale = transform.localScale;
        bodyScale.x *= -1;
        transform.localScale = bodyScale;
    }
		
    private void OnCollisionEnter2D(Collision2D collision) {
        if (collision.transform.tag == "Moving Platform") {
            transform.parent = collision.transform;
        }

		if (collision.transform.tag == "Deathzone") {
			transform.position = startPosition;
		}
    }

    private void OnCollisionExit2D(Collision2D collision) {
        if (collision.transform.tag == "Moving Platform") {
            transform.parent = null;
        }
    }
}
