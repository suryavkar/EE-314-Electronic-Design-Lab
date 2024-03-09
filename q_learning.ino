void get_reward()
{
  if (presx+presy == 2*grid_size-2)
    reward = 10.0;
  else{
    if (end_flag==1)
      reward = -10.0;
    else
      reward = -1.0;
  }
}

int act_to_index(char act)
{
  switch (act)
  {
    case 'u': 
      return 0;
      break;
    
    case 'l': 
      return 1;
      break;
    
    case 'd': 
      return 2;
      break;
    
    case 'r': 
      return 3;
      break;
    
    default:
      return -1;
  }
}

char index_to_act(int index)
{
  switch (index)
  {
    case 0: 
      return 'u';
      break;
    
    case 1: 
      return 'l';
      break;
    
    case 2: 
      return 'd';
      break;
    
    case 3: 
      return 'r';
      break;
    
    default:
      return 'k';
  }
}

int max_action()
{
  float max_act = -10000.00;
  int index_act = 0;
  for(int i_act=0;i_act<4;i_act++)
  {
    if (Q_table[grid_size*presy+presx][i_act] > max_act)
    {
      max_act = Q_table[grid_size*presy+presx][i_act];
      index_act = i_act;
    }
  }
  return index_act;
}

char get_act()
{
  int index_act;
  long rand = random(0,100);
  if(rand<(100-eps))
    index_act=max_action();
  else
    index_act = random(0,4);
  return index_to_act(index_act);
}

void update_Q()
{
  Q_table[grid_size*prevy+prevx][act_to_index(prev_act)] = (1.0-alpha)*Q_table[grid_size*prevy+prevx][act_to_index(prev_act)] + alpha*(reward+gamma*Q_table[grid_size*presy+presx][max_action()]);
}

int forbid_act()
{
  int nextx = presx;
  int nexty = presy;
  switch (pres_act)
  {
    case 'l':
    nextx=nextx-1;
    break;

    case 'd':
    nexty=nexty-1;
    break;

    case 'u':
    nexty=nexty+1;
    break;

    case 'r':
    nextx=nextx+1;
    break;

    default:
    break;
  }
  if ((nextx>=grid_size) || (nexty>=grid_size) || (nextx<0) || (nexty<0))
  {
    return 1;
  }
  else
    return 0;
}