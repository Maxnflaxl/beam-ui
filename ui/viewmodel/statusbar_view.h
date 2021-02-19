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

#pragma once

#include <QObject>
#include "model/wallet_model.h"
#include "model/helpers.h"

class StatusbarViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isOnline                READ getIsOnline            NOTIFY isOnlineChanged)
    Q_PROPERTY(bool isFailedStatus          READ getIsFailedStatus      NOTIFY isFailedStatusChanged)
    Q_PROPERTY(bool isSyncInProgress        READ getIsSyncInProgress    NOTIFY isSyncInProgressChanged)
    Q_PROPERTY(bool isConnectionTrusted     READ getIsConnectionTrusted NOTIFY isConnectionTrustedChanged)
    Q_PROPERTY(int nodeSyncProgress         READ getNodeSyncProgress    NOTIFY nodeSyncProgressChanged)
    Q_PROPERTY(QString branchName           READ getBranchName          CONSTANT)
    Q_PROPERTY(QString walletStatusErrorMsg READ getWalletStatusErrorMsg NOTIFY statusErrorChanged)
    Q_PROPERTY(QStringList blockchains      READ getBlockchains         NOTIFY blockchainsChanged)
    Q_PROPERTY(int currentBlockchainIndex   READ getCurrentBlockchainIndex WRITE setCurrentBlockchainIndex   NOTIFY currentBlockchainIndexChanged)

public:

    StatusbarViewModel();

    bool getIsOnline() const;
    bool getIsFailedStatus() const;
    bool getIsSyncInProgress() const;
    bool getIsConnectionTrusted() const;
    int getNodeSyncProgress() const;
    QString getBranchName() const;
    QString getWalletStatusErrorMsg() const;
    QStringList getBlockchains() const;

    void setIsOnline(bool value);
    void setIsFailedStatus(bool value);
    void setIsSyncInProgress(bool value);
    void setIsConnectionTrusted(bool value);
    void setNodeSyncProgress(int value);
    void setWalletStatusErrorMsg(const QString& value);

    int getCurrentBlockchainIndex() const;
    void setCurrentBlockchainIndex(int value);

public slots:

    void onNodeConnectionChanged(bool isNodeConnected);
    void onGetWalletError(beam::wallet::ErrorType error);
    void onSyncProgressUpdated(int done, int total);
    void onNodeSyncProgressUpdated(int done, int total);

signals:

    void isOnlineChanged();
    void isFailedStatusChanged();
    void isSyncInProgressChanged();
    void isConnectionTrustedChanged();
    void nodeSyncProgressChanged();
    void statusErrorChanged();
    void blockchainsChanged();
    void currentBlockchainIndexChanged();

private:
    QString getBlockchainName() const;
    void updateWalletModel();
private:
    WalletModel::Ptr m_model;

    Connections m_signalConnections;
    bool m_isOnline;
    bool m_isSyncInProgress;
    bool m_isFailedStatus;
    bool m_isConnectionTrusted;
    int m_nodeSyncProgress;

    int m_nodeDone;
    int m_nodeTotal;
    int m_done;
    int m_total;

    QString m_errorMsg;
    int m_currentBlockchainIndex;
};
