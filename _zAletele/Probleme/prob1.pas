uses crt;
var n,nr,put2,p,i,hep,put,dv:word;
    e:word;
    np:array[2..100] of boolean;
    //prima:boolean;

procedure afla_prime;
var hp:word;
begin
  hep :=round(sqrt(p));
  for i := 2 to hep do np[i] := true;
  for i := 2 to hep do
    if np[i] = true then
      for hp := 2 to (hep div i) do
        np[hp*i] := false;
end;

begin
  clrscr;
  write('n= '); readln(n);
  write('p= '); readln(p);

  afla_prime;

  e:= 10000;

  //for i := 2 to hep do if np[i]=true then writeln(i);
  for i := 2 to hep do
  begin
   if (np[i] = true) and ( p mod i =0) then
   begin
     dv := i ;
     put := 0;
     while p mod dv =0 do
     begin
       dv := dv * i;
       inc(put);
     end;

     nr := n ;
     put2 := 0;
     while nr div i <> 0 do
     begin
       put2 := put2 + nr div i;
       nr := nr div i;
     end;
     //writeln(i,' ',put2 div put);
     if e > put2 div put then e := put2 div put;
   end;
  end;


  writeln(e);
  read(e);









end.