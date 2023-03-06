using UnityEngine.SceneManagement;
using UnityEngine;

public class Animate_Script : MonoBehaviour
{
    private Animator MyAnim;
    private Rigidbody2D rigid;
    private SpriteRenderer flip;
    
    public bool bNotGrounded = false;
    public float moving;
    private int counter = 0;
    // Start is called before the first frame update
    void Start()
    {
        MyAnim = GetComponent<Animator>();
        rigid = GetComponent<Rigidbody2D>();
        flip = GetComponent<SpriteRenderer>();

        Debug.Log("Press ESC to exit");
    }

    // Update is called once per frame
    void Update()
    {
        moving = Input.GetAxisRaw("Horizontal");

        bool bIsRunning = Mathf.Abs(moving) > 0.1f;
        MyAnim.SetBool("IsRunning", bIsRunning);

        if (moving < 0)
        {
            flip.flipX = true;
        }
        else
        {
            flip.flipX = false;
        }
        rigid.velocity = new Vector2(moving * 4, rigid.velocity.y);
        if (rigid.velocity.y == 0)
        {
            bNotGrounded = false;
        }

        if (Input.GetKeyDown(KeyCode.Space))
        {
            bNotGrounded = true;
            rigid.AddForce(new Vector2(0, 200));
        }
       
        

        MyAnim.SetBool("NotGrounded", bNotGrounded);

        if (Input.GetKeyDown(KeyCode.Z))
        {
            MyAnim.SetTrigger("Pressed");
            counter++;
            MyAnim.SetInteger("TimesHurt", counter);
        }
        if (bNotGrounded == false && Input.GetKeyDown(KeyCode.X))
        {
            Attack();
        }
        if (Input.GetKeyDown(KeyCode.C))
        {
            Equip();
        }

        if (Input.GetKeyDown(KeyCode.Escape))
        {
            SceneManager.LoadScene("Main Menu");
        }
    }

    public void Attack()
    {        
            if (MyAnim.GetInteger("Equipped") == 1)
            {
                MyAnim.SetTrigger("IsAttacking");
            }
            else if (MyAnim.GetInteger("Equipped") == 2)
            {
                MyAnim.SetTrigger("IsAttacking");
            }
            else if (MyAnim.GetInteger("Equipped") == 3)
            {
                MyAnim.SetTrigger("IsAttacking");
            }                          
    }

    public void Equip()
    {
            if (MyAnim.GetInteger("Equipped") == 1)
            {
                MyAnim.SetInteger("Equipped", 2);
            }
            else if (MyAnim.GetInteger("Equipped") == 2)
            {
                MyAnim.SetInteger("Equipped", 3);
            }
            else if (MyAnim.GetInteger("Equipped") == 3)
            {
                MyAnim.SetInteger("Equipped", 1);
            }
    }

    public void Arrow()
    {
        GameObject fired = Instantiate(GameObject.Find("Arrow"), GameObject.Find("Roll_Credits").transform.position, Quaternion.identity);
        if (GameObject.Find("Roll_Credits").GetComponent<SpriteRenderer>().flipX) 
        {
            fired.GetComponent<Rigidbody2D>().velocity = new Vector2(-4, 0);
        }
        else if(!GameObject.Find("Roll_Credits").GetComponent<SpriteRenderer>().flipX)
        {
            fired.GetComponent<Rigidbody2D>().velocity = new Vector2(4, 0);
        }       
    }

    public void Spell()
    {
        Debug.Log("Spell");
    }

}
