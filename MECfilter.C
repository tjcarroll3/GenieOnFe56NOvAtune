void MECfilter(TString gstfile, TString outfile){

  TFile* input = new TFile(gstfile.Data());

  TTree* originaltree = (TTree*) input->Get("gst");

  TFile* outf = new TFile(outfile.Data(), "RECREATE");

  TTree* filteredtree = originaltree->CopyTree("cc&&mec");

  filteredtree->Write();

  outf->Close();
  input->Close();

}
