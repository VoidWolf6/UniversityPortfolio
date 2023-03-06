using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StarAction : MonoBehaviour
{
    public GameObject Stars;
    public GameObject R;
    public GameObject B;

    public float StarSpeed = 0.5f;
    public float Rx;
    public float Bx;
    public float Sx;

    private bool posit;
    // Start is called before the first frame update
    void Start()
    {
        posit = true;
    }

    // Update is called once per frame
    void Update()
    {
        Sx = Stars.transform.position.x;
        Rx = R.transform.position.x;
        Bx = B.transform.position.x;

        if (!B.GetComponent<Ships>().rotated)
        {
            if (posit)
                {                                  
                   if (Sx > Bx)
                   {
                       posit = false;
                   }
                   else
                   {
                       Stars.transform.Translate(new Vector2(StarSpeed * Time.deltaTime, 0)); 
                   }
                }
                else if (!posit)
                {            
                    if (Sx < Rx)
                    {
                        posit = true;
                    }
                    else
                    {
                        Stars.transform.Translate(new Vector2(-StarSpeed * Time.deltaTime, 0));
                    }
                }
        }
        else if (R.GetComponent<Ships>().rotated)
        {
            if (posit)
            {
                if (Sx > Rx)
                {
                    posit = false;
                }
                else
                {
                    Stars.transform.Translate(new Vector2(StarSpeed * Time.deltaTime, 0));
                }
            }
            else if (!posit)
            {
                if (Sx < Bx)
                {
                    posit = true;
                }
                else
                {
                    Stars.transform.Translate(new Vector2(-StarSpeed * Time.deltaTime, 0));
                }
            }
        }
    }

    
}
    
