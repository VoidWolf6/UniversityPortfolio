using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ArrowPlate : MonoBehaviour
{
    public GameObject Target;
    public GameObject ArrowPrefab;
    public GameObject Fired;

    public float spawnx;
    public float spawny;
    // Start is called before the first frame update
    void Start()
    {
        spawnx = Target.transform.position.x;
        spawny = Target.transform.position.y;
    }

    // Update is called once per frame
    void Update()
    {       
        
    }

    public void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.transform.name == "Character")
        {
            Fired = Instantiate(ArrowPrefab, new Vector2(spawnx, spawny), Quaternion.identity);
            Fired.GetComponent<Rigidbody2D>().velocity = new Vector2(10, 0);
        }
    }
}
