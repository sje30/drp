#include <Rcpp.h>
using namespace Rcpp;

/* Octave code was in ~/mosaics/code/drp */
//' Do the binning of the cross-correlation
//'
//' @param x1s Vector of x coordinates for type 1 cells
//' @param y1s Vector of y coordinates for type 1 cells
//' @param x2s Vector of x coordinates for type 2 cells
//' @param y2s Vector of y coordinates for type 2 cells
//' @param nbins Number of bins
//' @param r Bin width
//' @param do_auto Set to TRUE for auto-correlation
//' @export
// [[Rcpp::export]]
NumericVector binit3(NumericVector x1s, NumericVector y1s,
		     NumericVector x2s, NumericVector y2s,
		     int nbins, double r, int do_auto)
{
  /* First data set is (x1s, y1s) of length n1.  Second data set is
   * (x2s, y2s) of length n2.  For each point in data set 1, we find
   * the distance to each point in data set 2.  This distance is then
   * binned into one of NBINS values in NS, spaced R um apart.
   *
   * This is used by the DRP procedure and ensures that it is _quick_,
   * say for greater than 200 cells.  Another speed, maybe in R, is to
   * sort the points by their x-coordinate, so that we only have to
   * measure distance to a subset of cells.  This will take more
   * effort though.  This seems to work fine.
   */
     
  int i,j;
  Sfloat x1, y1, x2, y2, dx, dy, dist;
  int bin;
  NumericVector ns(nbins);
  int n1, n2;
  n1 = x1s.size(); n2=x2s.size();
  
  /*Rprintf("nbins is %d\n", nbins); */

  for(i=0; i<nbins; i++)
    /* clear the bins first. */
    ns[i]=0;
  

  for(i=0; i<n1; i++) {
    x1 = x1s[i]; y1 = y1s[i];

    for (j=0; j<n2; j++) {
      if (do_auto && i==j) {
	;
      } else {
	x2 = x2s[j]; y2 = y2s[j];
	dx = x1 - x2; dy = y1 - y2;
	dist = sqrt( (double) ((dx*dx) + (dy*dy)));
	bin = (int)(dist/r);
	if (bin < nbins)
	  ns[bin]++;
      }
    }
  }
  return(ns);
}

