using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Boom : MonoBehaviour
{
    public float Bomb_radius = 5.0F;
    public float Bomb_force = 10.0F;

    void Start()
    {
        Vector2 explosionPos = transform.position;
        Collider[] colliders = Physics.OverlapSphere(explosionPos, Bomb_radius);
        foreach (Collider hit in colliders)
        {
            Rigidbody rb = hit.GetComponent<Rigidbody>();

            if (rb != null)
                rb.AddExplosionForce(Bomb_force, explosionPos, Bomb_radius, 3.0F);
        }
    }
}
