using System;
using System.Threading.Tasks;
using Windows.UI.Xaml.Controls;
using RuntimeComponent;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace TestApp
{
    /// <summary>
    ///     An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            InitializeComponent();

            Task.Delay(1000)
                .ContinueWith(task =>
                {
                    GC.Collect();
                    //TestClass.TryUnload();
                });
        }
    }
}