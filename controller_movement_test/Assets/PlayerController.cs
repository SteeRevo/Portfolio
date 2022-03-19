using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class PlayerController : MonoBehaviour
{
    public PlayerInputActions playerInput;
    public Transform attackPoint;
    public float attackRange = 0.5f;
    public LayerMask enemyLayer;
    public int attackDamage = 40;
    
    public float attackRate = 2f;
    float nextattackTime = 0f;

    private Rigidbody2D rb;
    private SpriteRenderer _renderer;

    private InputAction attack;
    private InputAction dash;

    public float speed = 10f;

    public float dashSpeed = 30;
    public bool isDashing = false;
    public float StartDashTimer;
    float CurrentDashTimer;
    public float dashForce;
    Vector2 dashDirection;
    public float dashCooldown = 0f;

    private 
    // Start is called before the first frame update
    void Awake()
    {
        playerInput = new PlayerInputActions();
        rb = GetComponent<Rigidbody2D>();
        _renderer = GetComponent<SpriteRenderer>();
        if (_renderer == null)
        {
            Debug.LogError("Player Sprite is missing a renderer");
        }
    }

    private void OnEnable()
    {
        playerInput.Enable();
        attack = playerInput.Movement.Attack;
        attack.performed += Attack;

        dash = playerInput.Movement.Dash;
        dash.performed += Dash;

    }

    private void OnDisable()
    {
        playerInput.Disable();
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        //movement
        Vector2 moveInput = playerInput.Movement.Move.ReadValue<Vector2>();  
        Debug.Log("Dash cooldown: " + dashCooldown);
        if(dashCooldown > 0){
            dashCooldown -= Time.deltaTime;
        }
        if(isDashing && dashCooldown <= 0)
        {
            rb.velocity = Vector2.zero;
            rb.velocity =  dashDirection * dashSpeed * dashForce;

            CurrentDashTimer -= Time.deltaTime;

            if(CurrentDashTimer <= 0)
            {
                isDashing = false;
                dashCooldown = 2f;
            }
        }
        else{
            rb.velocity = moveInput * speed * Time.deltaTime; 
        }
        
        if(moveInput.x > 0){
            //_renderer.flipX = true;
            transform.localScale = new Vector3(-1f, 1f, 1f);
        }
        else if(moveInput.x < 0)
        {
            //_renderer.flipX = false;
            transform.localScale = new Vector3(1f, 1f, 1f);
        }

        

    }

    private void Attack(InputAction.CallbackContext context)
    {
        Debug.Log("attack");

        Collider2D[] hitEnemies = Physics2D.OverlapCircleAll(attackPoint.position, attackRange, enemyLayer);

        foreach(Collider2D enemy in hitEnemies)
        {
            enemy.GetComponent<Enemy>().TakeDamage(attackDamage);
        }
    }

    private void Dash(InputAction.CallbackContext context)
    {
        if(dashCooldown <= 0)
        {
            Debug.Log("dash");
            isDashing = true;
            CurrentDashTimer = StartDashTimer;
            rb.velocity = Vector2.zero;
            dashDirection = playerInput.Movement.Move.ReadValue<Vector2>();
        }
        
    }


    void OnDrawGizmosSelected()
    {
        if(attackPoint == null)
        {
            Debug.Log("no attack point");
            return;
        }
        Gizmos.DrawWireSphere(attackPoint.position, attackRange);
    }
}
