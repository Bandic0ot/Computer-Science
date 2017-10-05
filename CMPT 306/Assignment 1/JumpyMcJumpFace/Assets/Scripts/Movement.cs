using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Movement : MonoBehaviour {

    Rigidbody2D body;
    Animator animate;

    public float jump_force;
    public float move_force;

    public float maxSpeed = 10.0f;
    public Transform groundCheck;
    public LayerMask groundType;
    bool facingRight = true;
    bool isGrounded = false;
    float groundCheckRadius = 0.2f;


    // Use this for initialization
    void Start () {
        body = GetComponent<Rigidbody2D>();
        animate = GetComponent<Animator>();
	}
	
	// Update is called once per frame
	void Update () {
        if (Input.GetButtonDown("Jump"))
        {
            if (isGrounded)
            {
                body.AddForce(new Vector2(0, jump_force));
            }
        }
    }

    void FixedUpdate() {
        isGrounded = Physics2D.OverlapCircle(groundCheck.position, groundCheckRadius, groundType);
        animate.SetBool("Ground", isGrounded);

        float moveX = Input.GetAxis("Horizontal");

        body.AddForce(new Vector2(moveX * move_force, 0));

        animate.SetFloat("Speed", Mathf.Abs(moveX));

        if (moveX > 0 && !facingRight)
        {
            Flip();
        } else if(moveX < 0 && facingRight)
        {
            Flip();
        }
    }

    void Flip()
    {
        facingRight = !facingRight;

        Vector2 bodyScale = transform.localScale;
        bodyScale.x *= -1;
        transform.localScale = bodyScale;
    }
}
