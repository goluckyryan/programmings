void tree1w(){
   TFile f("tree1.root","recreate");
   TTree t1("t1","a simple Tree");
   Float_t px,py,pz;
   Int_t  ev;
   
   t1.Branch("px",&px,"px/F");
   t1.Branch("py",&py,"py/F");
   t1.Branch("pz",&pz,"pz/F");
   t1.Branch("ev",&ev,"ev/I");
   
   for(Int_t i =0 ; i< 10000; i++){
      gRandom->Rannor(px,py);
      pz = px*px + py*py;
      ev = i;
      t1.Fill();
   }
   
   t1.Write();
}
