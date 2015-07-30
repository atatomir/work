const max = 1000000;
type queue=record
       v,sel:longint;
       s:ansistring;
     end;
var n,i,j,v,x,left,right,sel,aux,t:longint;
    q:array[0..max]of queue;
    s,sl:ansistring;
    h:array[0..15]of byte;
    f:text;
    ap:array[0..2000000]of boolean;

function vGet(v,pos:longint):longint;
begin
  vGet := (v shr (2*(n-pos)))and 3;
end;

procedure vSet(var v:longint;pos,sv:longint); inline;
var aux,auxl:longint;
begin
  aux := 2*(n-pos);
  if sv = 0 then
  begin
    auxl := (1 shl aux-1)+((1 shl(2*n-aux-2)-1)shl(aux+2));
    v := v and auxl;
  end
  else
    v := v or (sv shl aux);
end;

procedure add_q(v,sel:longint;s:string);inline;
var p,x:longint;
begin
  x := 0;
  for p := n downto 1 do x := x*3 + vGet(v,p);

  if ap[x] then exit;
  ap[x] := true;

  inc(j);
  q[j].v := v; q[j].sel := sel; q[j].s := s;
end;

function verif(v:longint):boolean;
var i:longint;
begin
  verif := true;
  for i := 1 to left do
    if vGet(v,i) <> 1 then
    begin
      verif := false;
      break;
    end;
  for i := n downto n-right+1 do
    if vGet(v,i) <> 2 then
    begin
      verif := false;
      break;
    end;
end;


begin
  for i := 1 to 2000000 do ap[i] := false;

  readln(n);
  v := 0;
  left := 0; right := 0;

  for i := 1 to n do
  begin
    read(x);
    vSet(v,i,x);
    if x = 1 then inc(left) else     // stanga 1 , dreapta 2
    if x = 2 then inc(right);
  end;

  i := 1; j := 0;
  add_q(v,0,'');
  while i <= j do
  begin
    v := q[i].v; sel := q[i].sel; s := q[i].s;
    inc(i);

    for t := 1 to n do h[t] := vGet(v,t);

    if verif(v) then
    begin
      writeln(sel);
      writeln(s);
      exit;
    end
    else
    begin
      for t := 1 to n-1 do       //pentru 2
      begin
        if h[t] = 2 then
        begin
          if h[t+1] = 0 then
          begin
            aux := v;
            vSet(aux,t,0); vSet(aux,t+1,2);
            str(t,sl);
            add_q(aux,sel+1,s+sl+' ');
          end
          else
          if t < n-1 then
          begin
            if h[t+2] = 0 then
            begin
              aux := v;
              vSet(aux,t,0); vSet(aux,t+2,2);
              str(t,sl);
              add_q(aux,sel+1,s+sl+' ');
            end;
          end;
        end;
      end;

      for t := n downto 2 do       //pentru 1
      begin
        if h[t] = 1 then
        begin
          if h[t-1] = 0 then
          begin
            aux := v;
            vSet(aux,t,0); vSet(aux,t-1,1);
            str(t,sl);
            add_q(aux,sel+1,s+sl+' ');
          end
          else
          if t > 2 then
          begin
            if h[t-2] = 0 then
            begin
              aux := v;
              vSet(aux,t,0); vSet(aux,t-2,1);
              str(t,sl);
              add_q(aux,sel+1,s+sl+' ');
            end;
          end;
        end;
      end;


    end;
  end;
end.
