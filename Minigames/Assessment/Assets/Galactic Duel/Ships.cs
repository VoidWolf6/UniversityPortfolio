using UnityEngine;
using UnityEngine.SceneManagement;

public class Ships : MonoBehaviour
{
    public GameObject Red;
    public GameObject Blue;
    public GameObject Projectile;
    private GameObject Proj;
    public GameObject Stars;

    public float ShipSpeed = 0.1f;
    public float RedLives;
    public float BlueLives;

    private float InputFromRXaxis;
    private float InputFromRYaxis;
    private float InputFromBXaxis;
    private float InputFromBYaxis;
    private float RedLine;
    private float BlueLine;
    private float CurrentTimer;
    private float Interval = 1;

    public bool rotated = false;
    public bool IsParented;

    // Start is called before the first frame update
    void Start()
    {
        Stars = GameObject.Find("Star");
        IsParented = false;
        RedLives = 3;
        BlueLives = 3;

        Debug.Log("Press ESC to exit");
    }

    // Update is called once per frame
    void Update()
    {
        InputFromRXaxis = Input.GetAxisRaw("Horiz");
        InputFromRYaxis = Input.GetAxisRaw("Vert");
        InputFromBXaxis = Input.GetAxisRaw("ontal");
        InputFromBYaxis = Input.GetAxisRaw("ical");
        RedLine = Red.transform.position.x;
        BlueLine = Blue.transform.position.x;
        
        Red.transform.Translate(new Vector2(ShipSpeed * Time.deltaTime * InputFromRXaxis, 0), Space.World);
        Red.transform.Translate(new Vector2(0, ShipSpeed * Time.deltaTime * InputFromRYaxis), Space.World);
        Blue.transform.Translate(new Vector2(ShipSpeed * Time.deltaTime * InputFromBXaxis, 0), Space.World);
        Blue.transform.Translate(new Vector2(0, ShipSpeed * Time.deltaTime * InputFromBYaxis), Space.World);

        Rotate();

        CurrentTimer += Time.deltaTime;
        if (CurrentTimer > Interval)
        { 
            if (Input.GetButtonDown("RedFire"))
            { 
                RedFiring();
                CurrentTimer = 0;
            }
            else if (Input.GetButtonDown("BlueFire"))
            {
                BlueFiring();
                CurrentTimer = 0;
            }
        }

        if (Input.GetKeyDown(KeyCode.Z))
        {
            if (IsParented == false)
            {
                Stars.transform.SetParent(Red.transform);
                Stars.transform.position = new Vector2(Red.transform.position.x, 0);
                Stars.GetComponent<StarAction>().enabled = false;
                IsParented = true;
            }
            else if (IsParented == true)
            {
                Stars.transform.SetParent(null);
                Stars.GetComponent<StarAction>().enabled = true;               
                IsParented = false;
            }
        }

        if (Input.GetKeyDown(KeyCode.C))
        {
            foreach (var item in GameObject.FindGameObjectsWithTag("BlueProject"))
            {
                if (item.GetComponent<Rigidbody2D>() == true)
                {
                    item.GetComponent<Rigidbody2D>().gravityScale = 1;
                }               
            }
        }

        if (RedLives == 0)
        {
            Red.SetActive(false);
            Blue.SetActive(false);
            Debug.Log("Blue Wins!");
        }
        else if (BlueLives == 0)
        {
            Red.SetActive(false);
            Blue.SetActive(false);
            Debug.Log("Red Wins!");
        }

        if (Input.GetKeyDown(KeyCode.Escape))
        {
            SceneManager.LoadScene("Main Menu");
        }
    }



    void Rotate()
    {

        if (RedLine > BlueLine)
        {
            if (rotated == false)
            {
                rotated = !rotated;
                Red.GetComponent<SpriteRenderer>().flipX = false;
                Blue.GetComponent<SpriteRenderer>().flipX = true;

            }
        }
        else if (RedLine < BlueLine)
        {
            if (rotated == true)
            {
                rotated = !rotated;
                Red.GetComponent<SpriteRenderer>().flipX = true;
                Blue.GetComponent<SpriteRenderer>().flipX = false;
            }            
        }
    
    }

    void RedFiring()
    {
        Proj = Instantiate(Projectile, new Vector2(Red.transform.position.x, Red.transform.position.y), Quaternion.identity);           
        Proj.GetComponent<SpriteRenderer>().color = Red.GetComponent<SpriteRenderer>().color;
        Proj.AddComponent<Bullets>();
        Proj.GetComponent<Bullets>().self = Proj;
        Proj.GetComponent<Bullets>().Red = Red;
        Proj.GetComponent<Bullets>().Blue = Blue;
        Proj.GetComponent<Bullets>().tag = gameObject.tag = "RedProject";

    }
    void BlueFiring()
    {
        Proj = Instantiate(Projectile, new Vector2(Blue.transform.position.x, Blue.transform.position.y), Quaternion.identity);
        Proj.GetComponent<SpriteRenderer>().color = Blue.GetComponent<SpriteRenderer>().color;
        Proj.AddComponent<Bullets>();
        Proj.GetComponent<Bullets>().self = Proj;
        Proj.GetComponent<Bullets>().Red = Red;
        Proj.GetComponent<Bullets>().Blue = Blue;
        Proj.GetComponent<Bullets>().tag = gameObject.tag = "BlueProject";

    }
}
