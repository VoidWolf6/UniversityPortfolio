using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullets : MonoBehaviour
{

    public GameObject self;
    public GameObject Red;
    public GameObject Blue;

    public int BulletSpeed = 2;
    private int RedShots = 0;
    private int BlueShots = 0;
    private int destroyed = 0;


    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
       
            if (self.GetComponent<SpriteRenderer>().color == Red.GetComponent<SpriteRenderer>().color)
            {
                if (Red.GetComponent<Ships>().rotated == true)
                {
                    self.transform.Translate(new Vector2(-BulletSpeed * Time.deltaTime, 0));
                }
                else
                {
                    self.transform.Translate(new Vector2(BulletSpeed *Time.deltaTime, 0));
                }
                
            }
            else if (self.GetComponent<SpriteRenderer>().color == Blue.GetComponent<SpriteRenderer>().color)
            {
                if (Blue.GetComponent<Ships>().rotated == true)
                {
                    self.transform.Translate(new Vector2(BulletSpeed * Time.deltaTime, 0));
                }
                else
                {
                    self.transform.Translate(new Vector2(-BulletSpeed * Time.deltaTime, 0));
                }         
            }


        if (Input.GetKeyDown(KeyCode.X))
        {
            RedShots = 0;
            BlueShots = 0;
            foreach (var item in GameObject.FindGameObjectsWithTag("RedProject"))
            {
                RedShots++;
            }
            foreach (var item in GameObject.FindGameObjectsWithTag("BlueProject"))
            {
                BlueShots++;
            }
            Debug.Log("Amount of red bullets active: " + RedShots);
            Debug.Log("Amount of blue bullets active: " + BlueShots);
            Debug.Log("Amount of bullets destroyed: " + destroyed);
        }


        if (self.transform.position.x > 22)
        {
            Destroy(self);
            destroyed++;
        }
        else if (self.transform.position.x < -22)
        {
            Destroy(self);
            destroyed++;
        }
        
    }

    private void OnTriggerEnter2D(Collider2D damage)
    {
        if (damage.gameObject.name == "Blue")
        {
            if (self.GetComponent<SpriteRenderer>().color != Blue.GetComponent<SpriteRenderer>().color)
            {               
                damage.GetComponent<Ships>().BlueLives -= 0.5f;
                self.SetActive(false);
            }
        }

        if (damage.gameObject.name == "Red")
        {
            if (self.GetComponent<SpriteRenderer>().color != Red.GetComponent<SpriteRenderer>().color)
            {
                damage.GetComponent<Ships>().RedLives -= 0.5f;
                self.SetActive(false);
            }
        }
      
    }


}
