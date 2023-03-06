using System.Collections;
using System.Collections.Generic;
using UnityEngine;
public class FiniteStateMachine
{
    
    private AI Owner;
    private State CurrentState = null;
    public bool Team; //If true, the agent is on the blue team 

    // Start is called before the first frame update
    public void Start()
    {
        if (Owner._agentData.FriendlyTeam == AgentData.Teams.BlueTeam)
        {
            Team = true;
        }
        else if (Owner._agentData.FriendlyTeam == AgentData.Teams.RedTeam)
        {
            Team = false;
        }
        CurrentState.Enter(Owner);        
    }

    // Update is called once per frame
    public void Update()
    {
        if (CurrentState != null) CurrentState.Execute(Owner); 
    }

    public FiniteStateMachine(AI owner)
    {
        this.Owner = owner;
    }

    public void SetStartState(State startState)
    {
        startState.Enter(Owner);
        CurrentState = startState;
    }

    public State GetActiveState()
    {
        return CurrentState;
    }
    
    public void ChangeState(State newState)
    {
        if (CurrentState != null)
        {
            CurrentState.Exit(Owner);
        }

        CurrentState = newState;

        if (CurrentState != null)
        {
            CurrentState.Enter(Owner);
        }
    }


}


abstract public class State
{
    protected FiniteStateMachine currentfsm;

    abstract public void Enter(AI agent);
    abstract public void Execute(AI agent);
    abstract public void Exit(AI agent);
}

public sealed class SearchingForHealth : State
{
    public SearchingForHealth(FiniteStateMachine fsm)
    {
        currentfsm = fsm;
    }

    public override void Enter(AI agent)
    {
        
    }

    public override void Execute(AI agent)
    {
        Debug.Log("Executing SearchingForHealth");
        if (!agent._agentInventory.HasItem(Names.HealthKit))
        {            
            agent._agentActions.MoveToRandomLocation();
            GameObject target = agent._agentSenses.GetObjectInViewByName(Names.HealthKit);
            if (target != null)
            {
                agent._agentActions.MoveTo(target);
                if (agent._agentSenses.IsItemInReach(target))
                {
                        agent._agentActions.CollectItem(target);
                }
            }
            
        }
        else if (agent._agentInventory.HasItem(Names.HealthKit))
        {
            if (agent.IsEnemyScoring() && agent.IsFriendlyScoring())
            {
                currentfsm.ChangeState(new RetrieveFriendly(currentfsm));
            }
            else if (agent.IsEnemyScoring() && !agent.IsFriendlyScoring())
            {
                currentfsm.ChangeState(new RetrieveFriendly(currentfsm));
            }
            else if (!agent.IsEnemyScoring() && agent.IsFriendlyScoring())
            {
                currentfsm.ChangeState(new DefendHomeBase(currentfsm));
            }
            else if (!agent.IsEnemyScoring() && !agent.IsFriendlyScoring())
            {
                currentfsm.ChangeState(new HuntEnemy(currentfsm));
            }
        }


        if (agent._agentSenses.GetEnemiesInView() != null)
        {
            Vector3 escape = agent._agentSenses.GetFleeVectorFromTarget(agent._agentSenses.GetNearestEnemyInView());
            agent._agentActions.MoveTo(escape);
        }


    }

    public override void Exit(AI agent)
    {
        agent._agentActions.UseItem(agent._agentInventory.GetItem(Names.HealthKit));
    }
}

public sealed class RetrieveFriendly : State
{
    private string target;
    public RetrieveFriendly(FiniteStateMachine fsm)
    {
        currentfsm = fsm;
    }

    public override void Enter(AI agent)
    {
        if (currentfsm.Team)
        {
            target = Names.BlueFlag;
        }
        else
        {
            target = Names.RedFlag;
        }
        agent._agentActions.MoveTo(agent._agentData.EnemyBase);
    }

    public override void Execute(AI agent)
    {
        Debug.Log("Executing RetrieveFriendly");
        if (agent._agentSenses.GetObjectInViewByName(target) != null)
        {
            GameObject seek = agent._agentSenses.GetObjectInViewByName(target);
            agent._agentActions.MoveTo(seek);
            if (agent._agentSenses.IsItemInReach(seek))
            {
                agent._agentActions.CollectItem(seek);
                currentfsm.ChangeState(new ReturningHome(currentfsm));
            }
        }
        else
        {
            if (!agent._agentInventory.HasItem(target))
            {
                agent._agentActions.MoveToRandomLocation();
                GameObject seek = agent._agentSenses.GetObjectInViewByName(target);
                if (seek != null)
                {
                    agent._agentActions.MoveTo(seek);
                    if (agent._agentSenses.IsItemInReach(seek))
                    {
                        agent._agentActions.CollectItem(seek);
                    }
                }

            }
            else if (agent._agentInventory.HasItem(target))
            {
                currentfsm.ChangeState(new ReturningHome(currentfsm));
            }

        }

        if (agent._agentData.CurrentHitPoints <= (agent._agentData.MaxHitPoints * 0.3))
        {
            currentfsm.ChangeState(new SearchingForHealth(currentfsm));
        }
    }

    public override void Exit(AI agent)
    {
        
    }
}

public sealed class HuntEnemy : State 
{
    private string target;
    public HuntEnemy(FiniteStateMachine fsm)
    {
        currentfsm = fsm;
    }

    public override void Enter(AI agent)
    {
        if (currentfsm.Team)
        {
            target = Names.RedFlag;
        }
        else
        {
            target = Names.BlueFlag;
        }
        agent._agentActions.MoveTo(agent._agentData.EnemyBase);
    }

    public override void Execute(AI agent)
    {
        Debug.Log("Executing HuntEnemy");
        if (agent._agentSenses.GetObjectInViewByName(target) != null)
        {
            GameObject seek = agent._agentSenses.GetObjectInViewByName(target);
            agent._agentActions.MoveTo(seek);
            if (agent._agentSenses.IsItemInReach(seek))
            {
                agent._agentActions.CollectItem(seek);
                currentfsm.ChangeState(new ReturningHome(currentfsm));
            }
        }
        else
        {
            if (!agent._agentInventory.HasItem(target))
            {
                agent._agentActions.MoveToRandomLocation();
                GameObject seek = agent._agentSenses.GetObjectInViewByName(target);
                if (seek != null)
                {
                    agent._agentActions.MoveTo(seek);
                    if (agent._agentSenses.IsItemInReach(seek))
                    {
                        agent._agentActions.CollectItem(seek);                       
                    }
                }

            }
            else if (agent._agentInventory.HasItem(target))
            {
                currentfsm.ChangeState(new ReturningHome(currentfsm));
            }

        }

        if (agent._agentData.CurrentHitPoints <= (agent._agentData.MaxHitPoints * 0.3))
        {
            currentfsm.ChangeState(new SearchingForHealth(currentfsm));
        }
        else if (agent._agentSenses.GetEnemiesInView().Count > 0)
        {
            currentfsm.ChangeState(new Engaging(currentfsm));
        }



        if (agent.IsEnemyScoring())
        {
            currentfsm.ChangeState(new RetrieveFriendly(currentfsm));
        }
    }

    public override void Exit(AI agent)
    {
        
    }
}

public sealed class DefendHomeBase : State 
{
    public DefendHomeBase(FiniteStateMachine fsm)
    {
        currentfsm = fsm;
    }

    public override void Enter(AI agent)
    {
        agent._agentActions.MoveTo(agent._agentData.FriendlyBase);
    }

    public override void Execute(AI agent)
    {
        Debug.Log("Executing DefendHomeBase");
        if (agent._agentSenses.GetEnemiesInView() != null)
        {
            currentfsm.ChangeState(new Engaging(currentfsm));
        }
        else if (agent._agentSenses.GetObjectInViewByName(Names.PowerUp) != null)
        {
            currentfsm.ChangeState(new SearchingForBoost(currentfsm));
        }


        if (agent._agentData.CurrentHitPoints <= (agent._agentData.MaxHitPoints * 0.3))
        {
            currentfsm.ChangeState(new SearchingForHealth(currentfsm));
        }
    }

    public override void Exit(AI agent)
    {
        
    }
}

public sealed class Engaging : State
{
    GameObject target;
    public Engaging(FiniteStateMachine fsm)
    {
        currentfsm = fsm;
    }

    public override void Enter(AI agent)
    {
        target = agent._agentSenses.GetNearestEnemyInView();
    }

    public override void Execute(AI agent)
    {
        Debug.Log("Executing Engaging");
        if (agent._agentSenses.IsInAttackRange(target) && agent._agentInventory.HasItem(Names.PowerUp))
        {
            GameObject boost = agent._agentInventory.GetItem(Names.PowerUp);
            agent._agentActions.UseItem(boost);
        }
        else if (agent._agentSenses.IsInAttackRange(target))
        {
            agent._agentActions.AttackEnemy(target);
        }
        else if (agent._agentSenses.GetEnemiesInView().Count >= 1 && agent._agentSenses.GetFriendliesInView().Count > 0)
        {
            currentfsm.ChangeState(new ReturningHome(currentfsm));
        }
        else
        {
            agent._agentActions.MoveTo(target);
        }



        if (agent._agentSenses.GetEnemiesInView() == null)
        {
            if (agent._agentData.CurrentHitPoints <= (agent._agentData.MaxHitPoints * 0.3))
            {
                currentfsm.ChangeState(new SearchingForHealth(currentfsm));
            }
            else if (agent.IsEnemyScoring() && agent.IsFriendlyScoring())
            {
                currentfsm.ChangeState(new RetrieveFriendly(currentfsm));
            }
            else if (agent.IsEnemyScoring() && !agent.IsFriendlyScoring())
            {
                currentfsm.ChangeState(new RetrieveFriendly(currentfsm));
            }
            else if (!agent.IsEnemyScoring() && agent.IsFriendlyScoring())
            {
                currentfsm.ChangeState(new DefendHomeBase(currentfsm));
            }
            else if (!agent.IsEnemyScoring() && !agent.IsFriendlyScoring())
            {
                currentfsm.ChangeState(new HuntEnemy(currentfsm));
            }
        }
    }

    public override void Exit(AI agent)
    {
        
    }
}

public sealed class ReturningHome : State
{
    GameObject path;
    public ReturningHome(FiniteStateMachine fsm)
    {
        currentfsm = fsm;
    }

    public override void Enter(AI agent)
    {
        path = agent._agentData.FriendlyBase;
    }

    public override void Execute(AI agent)
    {
        Debug.Log("Executing ReturningHome");
        if (agent._agentSenses.GetEnemiesInView() != null && agent._agentData.HasFriendlyFlag)
        {
            Vector3 escape = agent._agentSenses.GetFleeVectorFromTarget(agent._agentSenses.GetNearestEnemyInView());
            agent._agentActions.MoveTo(escape);
        }
        else if (agent._agentSenses.GetEnemiesInView() != null && agent._agentData.HasEnemyFlag && agent._agentData.CurrentHitPoints >= (agent._agentData.MaxHitPoints / 2))
        {
            currentfsm.ChangeState(new Engaging(currentfsm));
        }
        else if (agent._agentSenses.GetEnemiesInView() != null && agent._agentData.HasEnemyFlag && agent._agentData.CurrentHitPoints < (agent._agentData.MaxHitPoints / 2))
        {
            Vector3 escape = agent._agentSenses.GetFleeVectorFromTarget(agent._agentSenses.GetNearestEnemyInView());
            agent._agentActions.MoveTo(escape);
        }
        else if (agent._agentData.CurrentHitPoints <= (agent._agentData.MaxHitPoints * 0.3))
        {
            currentfsm.ChangeState(new SearchingForHealth(currentfsm));
        }
        else
        {
            agent._agentActions.MoveTo(path);           
            if (agent.IsEnemyScoring() && agent.IsFriendlyScoring())
            {
                currentfsm.ChangeState(new RetrieveFriendly(currentfsm));
            }
            else if (agent.IsEnemyScoring() && !agent.IsFriendlyScoring())
            {
                currentfsm.ChangeState(new RetrieveFriendly(currentfsm));
            }
            else if (!agent.IsEnemyScoring() && agent.IsFriendlyScoring())
            {
                currentfsm.ChangeState(new DefendHomeBase(currentfsm));
            }
            else if (!agent.IsEnemyScoring() && !agent.IsFriendlyScoring())
            {
                currentfsm.ChangeState(new HuntEnemy(currentfsm));
            }
        }

    }

    public override void Exit(AI agent)
    {
        if (agent._agentData.HasFriendlyFlag && currentfsm.Team)
        {
            agent._agentActions.DropItem(agent._agentInventory.GetItem(Names.BlueFlag));
        }
        else if (agent._agentData.HasEnemyFlag && currentfsm.Team)
        {
            agent._agentActions.DropItem(agent._agentInventory.GetItem(Names.RedFlag));
        }
        else if (agent._agentData.HasFriendlyFlag && !currentfsm.Team)
        {
            agent._agentActions.DropItem(agent._agentInventory.GetItem(Names.RedFlag));
        }
        else if (agent._agentData.HasEnemyFlag && !currentfsm.Team)
        {
            agent._agentActions.DropItem(agent._agentInventory.GetItem(Names.BlueFlag));
        }
    }
}

public sealed class SearchingForBoost : State 
{
    public SearchingForBoost(FiniteStateMachine fsm)
    {
        currentfsm = fsm;
    }

    public override void Enter(AI agent)
    {

    }

    public override void Execute(AI agent)
    {
        Debug.Log("Executing SearchingForBoost");
        if (!agent._agentInventory.HasItem(Names.PowerUp))
        {
            GameObject target = agent._agentSenses.GetObjectInViewByName(Names.PowerUp);
            agent._agentActions.MoveTo(target);
            if (agent._agentSenses.IsItemInReach(target))
            {
                agent._agentActions.CollectItem(target);
            }

        }
        else if (agent._agentInventory.HasItem(Names.PowerUp))
        {
            if (agent.IsEnemyScoring() && agent.IsFriendlyScoring())
            {
                currentfsm.ChangeState(new RetrieveFriendly(currentfsm));
            }
            else if (agent.IsEnemyScoring() && !agent.IsFriendlyScoring())
            {
                currentfsm.ChangeState(new RetrieveFriendly(currentfsm));
            }
            else if (!agent.IsEnemyScoring() && agent.IsFriendlyScoring())
            {
                currentfsm.ChangeState(new DefendHomeBase(currentfsm));
            }
            else if (!agent.IsEnemyScoring() && !agent.IsFriendlyScoring())
            {
                currentfsm.ChangeState(new HuntEnemy(currentfsm));
            }
        }

    }

    public override void Exit(AI agent)
    {
        
    }

}