using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Pivot : MonoBehaviour
{
    public Transform pivoting;
    public float degreesPerSecond;

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        pivoting.transform.Rotate(Vector3.back, degreesPerSecond * Time.deltaTime, Space.Self);
    }


    private void OnCollision2DEnter(Collider2D collision)
    {
        if (collision.transform.name == "SteelArrow")
        {
            Physics2D.IgnoreCollision(pivoting.GetComponent<Collider2D>(), collision.GetComponent<Collider2D>(), true);
        }
    }
}
