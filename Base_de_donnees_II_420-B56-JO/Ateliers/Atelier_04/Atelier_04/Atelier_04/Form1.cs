using Microsoft.VisualBasic;
using System.Data.SqlClient;

namespace Atelier_04
{
  public partial class Form1 : Form
  {
    SqlConnection _conn;
    SqlCommand _cmd;
    SqlDataReader _reader;
    string[] _toAdd;


    public Form1()
    {
      InitializeComponent();
      _conn = new SqlConnection("Data Source='J-C236-OL-15';Initial Catalog='Atelier_03';User Id='Atelier';Password='atelier'");
      _conn.Open();
    }

    private void Form1_Load(object sender, EventArgs e)
    {
      lstFilms.View = View.Details;
      lstFilms.FullRowSelect = true;
      lstFilms.MultiSelect = false;
      lstFilms.Columns.Add("Id", 0);
      lstFilms.Columns.Add("Titre", lstFilms.Width);
      lstFilms.Items.Clear();

      _cmd = new SqlCommand("SELECT * FROM Films", _conn);
      _reader = _cmd.ExecuteReader();

      _toAdd = new string[2];
      while (_reader.Read())
      {
        _toAdd[0] = _reader["FilmCode"].ToString();
        _toAdd[1] = _reader["FilmTitre"].ToString();
        lstFilms.Items.Add(new ListViewItem(_toAdd));
      }
      _reader.Close();

      lstAct.View = View.Details;
      lstAct.FullRowSelect = true;
      lstAct.MultiSelect = false;
      lstAct.Columns.Add("ID", 0);
      lstAct.Columns.Add("Nom", lstAct.Width / 2);
      lstAct.Columns.Add("Prénom", lstAct.Width / 2);
      lstAct.Items.Clear();

      _cmd = new SqlCommand("SELECT * FROM Acteurs", _conn);
      _reader = _cmd.ExecuteReader();

      _toAdd = new string[3];
      while (_reader.Read())
      {
        _toAdd[0] = _reader["ActCode"].ToString();
        _toAdd[1] = _reader["ActNom"].ToString();
        _toAdd[2] = _reader["ActPrénom"].ToString();
        lstAct.Items.Add(new ListViewItem(_toAdd));
      }
      _reader.Close();
      lstAct.Items[0].Selected = true;

      lstDist.View = View.Details;
      lstDist.FullRowSelect = true;
      lstDist.MultiSelect = false;
      lstDist.Columns.Add("ActID", 0);
      lstDist.Columns.Add("FilmID", 0);
      lstDist.Columns.Add("Rôle", lstDist.Width / 2);
      lstDist.Columns.Add("Acteur", lstDist.Width / 2);
      lstDist.Items.Clear();
    }

    private void lstFilms_SelectedIndexChanged(object sender, EventArgs e)
    {
      UpdateLstDist();
    }

    private void lstDist_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (lstDist.SelectedItems.Count <= 0) return;

      txbRole.Text = lstDist.SelectedItems[0].SubItems[2].Text;
    }

    private void btnAjouter_Click(object sender, EventArgs e)
    {
      if (lstFilms.SelectedItems.Count <= 0) return;
      if (lstAct.SelectedItems.Count <= 0) return;
      if (txbRole.Text == "") return;
      
      _cmd = new SqlCommand("psAjouterRole", _conn);
      _cmd.CommandType = System.Data.CommandType.StoredProcedure;
      _cmd.Parameters.AddWithValue("@actCode", lstAct.SelectedItems[0].SubItems[0].Text);
      _cmd.Parameters.AddWithValue("@filmCode", lstFilms.SelectedItems[0].SubItems[0].Text);
      _cmd.Parameters.AddWithValue("@role", txbRole.Text);
      _cmd.ExecuteNonQuery();

      UpdateLstDist();
      lstDist.Items[lstDist.Items.Count - 1].Selected = true;
    }

    private void btnSupprimer_Click(object sender, EventArgs e)
    {
      if (lstDist.SelectedItems.Count <= 0) return;

      _cmd = new SqlCommand("psSupprimerRole", _conn);
      _cmd.CommandType = System.Data.CommandType.StoredProcedure;
      _cmd.Parameters.AddWithValue("@actCode", lstDist.SelectedItems[0].SubItems[0].Text);
      _cmd.Parameters.AddWithValue("@filmCode", lstDist.SelectedItems[0].SubItems[1].Text);
      _cmd.Parameters.AddWithValue("@role", lstDist.SelectedItems[0].SubItems[2].Text);
      _cmd.ExecuteNonQuery();

      UpdateLstDist();
    }

    private void UpdateLstDist()
    {
      if (lstFilms.SelectedItems.Count <= 0) return;

      string query = "SELECT * FROM fnDistribution(" + lstFilms.SelectedItems[0].SubItems[0].Text + ") ORDER BY ActNom";
      _cmd = new SqlCommand(query, _conn);
      _reader = _cmd.ExecuteReader();

      _toAdd = new string[4];
      lstDist.Items.Clear();
      while (_reader.Read())
      {
        _toAdd[0] = _reader["ActCode"].ToString();
        _toAdd[1] = _reader["FilmCode"].ToString();
        _toAdd[2] = _reader["DistRôle"].ToString();
        _toAdd[3] = _reader["ActPrénom"].ToString() + " " + _reader["ActNom"].ToString();
        lstDist.Items.Add(new ListViewItem(_toAdd));
      }
      _reader.Close();

      lstDist.Items[0].Selected = true;
    }
  }
}