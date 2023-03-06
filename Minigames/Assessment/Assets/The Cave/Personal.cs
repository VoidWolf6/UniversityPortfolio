using UnityEngine.SceneManagement;
using UnityEngine;

public class Personal : MonoBehaviour
{
    public float move;
    public GameObject self;
    public Rigidbody2D ri;

    // Start is called before the first frame update
    void Start()
    {
        ri = self.GetComponent<Rigidbody2D>();

        Debug.Log("Press ESC to exit");
    }

    // Update is called once per frame
    void Update()
    {
        move = 5 * Input.GetAxis("Horizontal");

        ri.velocity = new Vector2(move, ri.velocity.y);

        if (Input.GetKeyDown(KeyCode.Space))
        {
            ri.AddForce(new Vector2(0, 400));
        }

        var hits2D = Physics2D.RaycastAll(transform.position, transform.right, 1.2f);
        foreach (var item in hits2D)
        {
            if (item.transform.name == "Button")
            {
                GameObject.Find("Door").GetComponent<Rigidbody2D>().AddForce(Vector2.up);
            }
        }

        if (Input.GetKeyDown(KeyCode.Escape))
        {
            SceneManager.LoadScene("Main Menu");
        }
    }

    public void OnCollisionEnter2D(Collision2D collide)
    {
        if (collide.transform.name == "SteelArrow")
        {
            self.GetComponent<UsefulScript>().KillPlayer();
        }
        else if (collide.transform.name == "Trap_Axe")
        {
            self.GetComponent<UsefulScript>().KillPlayer();
        }
    }

}
