// Copyright 2018 The Beam Team
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "main_view.h"
#include "model/app_model.h"
#include <QApplication>
#include <QClipboard>
#include "qml_globals.h"
#include "wallet/client/apps_api/apps_utils.h"
using namespace beam;
namespace
{
    const int msInMinute = 60 * 1000;
    const int LockTimeouts[] =
    {
        0 * msInMinute,
        1 * msInMinute,
        5 * msInMinute,
        15 * msInMinute,
        30 * msInMinute,
        60 * msInMinute,
    };

    const int minResetPeriodInMs = 1000;
}

MainViewModel::MainViewModel()
    : m_settings{AppModel::getInstance().getSettings()}
    , m_timer(this)
{
    m_timer.setSingleShot(true);
    
    auto walletModelPtr = AppModel::getInstance().getWalletModel();

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(lockWallet()));
    connect(&m_settings, SIGNAL(lockTimeoutChanged()), this, SLOT(onLockTimeoutChanged()));
    connect(&m_settings, SIGNAL(generalMouseEvent()), this, SLOT(onGeneralMouseEvent()));
    connect(walletModelPtr, &WalletModel::walletStatusChanged, this, &MainViewModel::unsafeTxCountChanged);
    connect(walletModelPtr, SIGNAL(transactionsChanged(beam::wallet::ChangeAction, const std::vector<beam::wallet::TxDescription>&)), SIGNAL(unsafeTxCountChanged()));
    connect(walletModelPtr, SIGNAL(notificationsChanged(beam::wallet::ChangeAction, const std::vector<beam::wallet::Notification>&)), SIGNAL(unreadNotificationsChanged()));
    connect(walletModelPtr, SIGNAL(devStateChanged(const QString&, int)), SLOT(onDevStateChanged(const QString&, int)));
#if defined(BEAM_HW_WALLET)
    connect(walletModelPtr, SIGNAL(showTrezorMessage()), this, SIGNAL(showTrezorMessage()));
    connect(walletModelPtr, SIGNAL(hideTrezorMessage()), this, SIGNAL(hideTrezorMessage()));
    connect(walletModelPtr, SIGNAL(showTrezorError(const QString&)), this, SIGNAL(showTrezorError(const QString&)));
#endif
    connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(onClipboardDataChanged()));

    onLockTimeoutChanged();
    m_settings.maxPrivacyLockTimeLimitInit();
    m_settings.minConfirmationsInit();
}

void MainViewModel::lockWallet()
{
    emit gotoStartScreen();
}

void MainViewModel::onLockTimeoutChanged()
{
    int index = m_settings.getLockTimeout();

    assert(static_cast<size_t>(index) < sizeof(LockTimeouts) / sizeof(LockTimeouts[0]));

    if (index > 0)
    {
        m_timer.start(LockTimeouts[index]);
    }
    else
    {
        m_timer.stop();
    }
}

void MainViewModel::onGeneralMouseEvent()
{
    resetLockTimer();
}

void MainViewModel::onDevStateChanged(const QString& sErr, int state)
{
    auto eState = static_cast<beam::wallet::HidKeyKeeper::DevState>(state);

    if (beam::wallet::HidKeyKeeper::DevState::Disconnected == eState ||
        beam::wallet::HidKeyKeeper::DevState::Stalled == eState)
    {
        if (getUnsafeTxCount())
            emit hwError("error");
    }
    else
    {
        emit hwError("");
    }
}

void MainViewModel::onClipboardDataChanged()
{
    auto text = QApplication::clipboard()->text();
    if (QMLGlobals::isToken(text))
    {
        //% "Address copied to clipboard"
        emit clipboardChanged(qtTrId("notification-address-copied"));
    }
}

void MainViewModel::resetLockTimer()
{
    if (m_timer.isActive() && (m_timer.interval() - m_timer.remainingTime() > minResetPeriodInMs))
    {
        m_timer.start();
    }
}

int MainViewModel::getUnsafeTxCount() const
{
    return static_cast<int>(AppModel::getInstance().getWalletModel()->getUnsafeActiveTransactionsCount());
}

int MainViewModel::getUnreadNotifications() const
{
    return static_cast<int>(AppModel::getInstance().getWalletModel()->getUnreadNotificationsCount());
}

QString MainViewModel::getDaoCoreAppID() const
{
    using namespace beam;
    const std::string appName = "BeamX DAO";
    std::string appURL  = "";
    switch (Rules::get().m_Network)
    {
    case Rules::Network::testnet:
        appURL = "https://apps-testnet.beam.mw/app/dao-core-app/index.html";
        break;
    case Rules::Network::mainnet:
        appURL = "https://apps.beam.mw/app/dao-core-app/index.html";
        break;
    case Rules::Network::dappnet:
        appURL = "http://3.16.160.95:80/app/plugin-dao-core/index.html";
        break;
    case Rules::Network::masternet:
        appURL = "http://3.19.32.148:80/app/plugin-dao-core/index.html";
        break;
    }

    const auto appid = beam::wallet::GenerateAppID(appName, appURL);
    return QString::fromStdString(appid);
}

QString MainViewModel::getVotingAppID() const
{
    const std::string appName = "BeamX DAO Voting";
    std::string appURL  = "";
    switch (Rules::get().m_Network)
    {
    case Rules::Network::testnet:
        appURL = "https://apps-testnet.beam.mw/app/dao-voting-app/index.html";
        break;
    case Rules::Network::mainnet:
        appURL = "https://apps.beam.mw/app/dao-voting-app/index.html";
        break;
    case Rules::Network::dappnet:
        appURL = "http://3.16.160.95:80/app-same-origin/dao-voting-app/index.html";
        break;
    case Rules::Network::masternet:
        appURL = "http://3.19.32.148:80/app-same-origin/dao-voting-app/index.html";
        break;
    }

    const auto appid = beam::wallet::GenerateAppID(appName, appURL);
    return QString::fromStdString(appid);
}

QString MainViewModel::getFaucetAppID() const
{
    const std::string appName = "BEAM Faucet";
    std::string appURL  = "";

    switch (Rules::get().m_Network)
    {
    case Rules::Network::testnet:
        appURL = "https://apps-testnet.beam.mw/app/plugin-faucet/index.html";
        break;
    case Rules::Network::mainnet:
        appURL = "https://apps.beam.mw/app/plugin-faucet/index.html";
        break;
    case Rules::Network::dappnet:
        appURL = "http://3.16.160.95:80/app/plugin-faucet/index.html";
        break;
    case Rules::Network::masternet:
        appURL = "http://3.19.32.148:80/app/plugin-faucet/index.html";
        break;
    }

    const auto appid = beam::wallet::GenerateAppID(appName, appURL);
    return QString::fromStdString(appid);
}

QString MainViewModel::getEthBridgeAppID() const
{
    std::string appName = "Bridges app";
    std::string appURL = "";

    switch (Rules::get().m_Network)
    {
    case Rules::Network::testnet:
        appURL = "https://apps-testnet.beam.mw/app/beam-bridge-app/index.html";
        break;
    case Rules::Network::mainnet:
        appURL = "https://apps.beam.mw/app/beam-bridge-app/index.html";
        break;
    case Rules::Network::dappnet:
        appURL = "http://3.16.160.95:80/app/beam-bridge-app/index.html";
        break;
    case Rules::Network::masternet:
        appName = "Bridge app";
        appURL = "http://3.19.32.148:80/app/beam-bridge-app/index.html";
        break;
    }

    const auto appid = beam::wallet::GenerateAppID(appName, appURL);
    return QString::fromStdString(appid);
}

bool MainViewModel::getDevMode() const
{
    return m_settings.getDevMode();
}

QString MainViewModel::getAccountLabel() const
{
    return m_settings.getAccountLabel();
}

QString MainViewModel::getAccountPicture() const
{
    return WalletSettings::getAccountPictureByIndex(m_settings.getAccountPictureIndex());
}